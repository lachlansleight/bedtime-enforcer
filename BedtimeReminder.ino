#include "src/menu/DisplayHandling.h"
#include "src/menu/MenuDisplay.h"
#include "src/menu/MenuControl.h"
#include "src/menu/InputHandling.h"
#include "src/devices/ScaleHandling.h"
#include "src/devices/Buzzer.h"
#include "src/devices/RTC.h"

#include "src/lib/TimeHandling.h"
#include "src/lib/config.h"

void setup()
{
    Serial.begin(115200);
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
    buzzer.initialize(PIN_BUZZR, 1000);
    showInitMessage("Initializing Clock");
    rtc.begin(14, 57);
    showInitMessage("Ready!");
    delay(500);
    display.clearDisplay();
}

void loop()
{
    timeTick();
    loopInputs();
    rtc.update();

    scale.updateMass(1);

    displayDebug(ButtonR.is, ButtonX.is, encoderPos, scale.massG, rtc.getTimeString(true));
    bool both = ButtonR.is && ButtonX.is;
    if(both && !buzzer.is) buzzer.on();
    if(!both && buzzer.is) buzzer.off();
    //printDebug();
}

void printDebug()
{
    Serial.println("");
    Serial.println("X: " + String(ButtonX.is) + " A: " + " R: " + String(ButtonR.is));
    Serial.println("Encoder: " + String(encoderPos));
    Serial.println("Scale: " + String(scale.massG, 1) + "g");
}