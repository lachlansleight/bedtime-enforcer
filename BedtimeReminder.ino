#include "src/lib/config.h"
#include "src/lib/TimeHandling.h"

#include "src/devices/ScaleHandling.h"
#include "src/devices/Buzzer.h"
#include "src/devices/RTC.h"

#include "src/menu/DisplayHandling.h"
#include "src/menu/MenuDisplay.h"
#include "src/menu/MenuControl.h"
#include "src/menu/InputHandling.h"

bool isBuzzing = false;
float freqOscillateT = 0.0;
bool isFreqOscillating = true;

void setup()
{
    //Serial.begin(115200);
    setupDisplay();
    showInitMessage("");
    delay(1000);
    showInitMessage("Loading Config");
    initializeConfig();
    delay(500);
    showInitMessage("Initializing Scale");
    scale.setupScale();
    showInitMessage("Initializing Inputs");
    setupInputs();
    buzzer.initialize(PIN_BUZZR, buzzerFreq);
    showInitMessage("Initializing Clock");
    rtc.begin();
    showInitMessage("Ready!");
    delay(500);
    display.clearDisplay();

    //uncomment this line if you need to tune your buzzer
    //uiMode = MODE_TUNE;
}

void loop()
{
    timeTick();
    loopInputs();
    rtc.update();

    if(uiMode == MODE_HOME || isBuzzing) scale.updateMass(1);

    // BUZZER TUNE - ENABLE THIS EXPLICITLY TO TUNE YOUR PARTICULAR PIEZO BUZZER
    if(uiMode == MODE_TUNE) {
        showTune(buzzerFreq);
        
        if(isFreqOscillating) {
            freqOscillateT += ((float)deltaMillis / 1000.0) / 10;
            buzzerFreq = (int)(sin(freqOscillateT) * 5000 + 5000);
        } else {
            buzzerFreq += encoder * 10;
            if(buzzerFreq <= 0) buzzerFreq = 10;
        }

        if(ButtonX.is) {
            buzzer.off();
            buzzer.on(buzzerFreq);
        }
        else buzzer.off();

        if(ButtonR.down) isFreqOscillating = !isFreqOscillating;
        return;
    }
    //displayDebug(ButtonR.is, ButtonX.is, encoderPos, scale.massG, rtc.getString(true));
    //return;
    
    //There's a two hour window after the alarm trigger time during which the alarm
    //will sound if the weight isn't within tolerance of the target weight.
    //Note that this wraps around 00:00 if necessary.
    int currentFullMinute = rtc.hour * 60 + rtc.minute;
    int minMinute = alarmHour * 60 + alarmMinute;
    int endMinute = (minMinute + alarmPeriod) % 1440;
    bool within = endMinute > minMinute 
        ? (minMinute <= currentFullMinute && currentFullMinute <= endMinute)
        : (minMinute <= currentFullMinute || currentFullMinute <= endMinute);
    if(!isBuzzing) {
        buzzer.off();
        
        if(within && abs(scale.massG - weight) > weightTolerance) {
            isBuzzing = true;
            uiMode = MODE_BUZZ;
        }
    } else {
        if((millis() / 1000) % 2 == 0) buzzer.on(buzzerFreq);
        else buzzer.off();

        if(abs(scale.massG - weight) <= weightTolerance) {
            isBuzzing = false;
            uiMode = MODE_HOME;
            buzzer.off();
        }
    }

    runUi();

    //bool both = ButtonR.is && ButtonX.is;
    //if(both && !buzzer.is) buzzer.on(buzzerFreq);
    //if(!both && buzzer.is) buzzer.off();
    //printDebug();
}

void printDebug()
{
    Serial.println("");
    Serial.println("X: " + String(ButtonX.is) + " A: " + " R: " + String(ButtonR.is));
    Serial.println("Encoder: " + String(encoderPos));
    Serial.println("Scale: " + String(scale.massG, 1) + "g");
}