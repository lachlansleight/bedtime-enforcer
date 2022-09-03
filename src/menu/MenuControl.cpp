#include "./MenuControl.h"

int uiMode = 0;
int mainMenuSelection = 0;
int autoExtractionPhase = 0;
int newTimeHour = 0;
int newTimeMinute = 0;
int timePosition = 0;
bool timeSetting = false;

void runUi() {
    if(uiMode == MODE_HOME) runHome();
    else if(uiMode == MODE_MENU) runMenu();
    else if(uiMode == MODE_SET) runSet();
    else if(uiMode == MODE_TIME) runSetTime();
    else if(uiMode == MODE_BUZZ) runBuzz();
}

void runHome() {
    if(ButtonR.down) {
        uiMode = MODE_MENU;
        mainMenuSelection = 0;
        return;
    }

    if(ButtonX.down) {
        showTare();
        scale.tare();
        delay(1000);
    }

    showHomeScreen(rtc.getString(false, rtc.second % 2 == 0), scale.massG);
}

void runMenu() {
    //navigate the menu
    if(encoder > 0 && mainMenuSelection < SET_CALIBRATION) mainMenuSelection++;
    else if(encoder < 0 && mainMenuSelection > SET_TIME) mainMenuSelection--;

    if(ButtonR.down) {
        if(mainMenuSelection == SET_CALIBRATION) {
            runAutoCalibrate(195.0); //this is just how much my smartphone happens to weigh right now
        } else if(mainMenuSelection == SET_TIME) {
            uiMode = MODE_TIME;
            newTimeHour = (int)rtc.hour;
            newTimeMinute = (int)rtc.minute;
            timeSetting = false;
            timePosition = 0;
        } else if(mainMenuSelection == SET_ALARM) {
            uiMode = MODE_TIME;
            newTimeHour = alarmHour;
            newTimeMinute = alarmMinute;
            timeSetting = false;
            timePosition = 0;
        } else {
            uiMode = MODE_SET;
        }
        return;
    }

    if(ButtonX.down) {
        uiMode = MODE_HOME;
        return;
    }

    showMainMenu(mainMenuSelection);
}

void runSet() {
    String heading = "";
    if(mainMenuSelection == SET_WEIGHT) {
        weight += float(encoder) * 5;
        if(weight <= 0) weight = 0;
        if(weight >= 500) weight = 500;
        heading = "Set Weight";
        showSetMenu(heading, String(weight, 1) + "g");
    } else if(mainMenuSelection == SET_TOLERANCE) {
        heading = "Set Tolerance";
        weightTolerance += float(encoder) * 1;
        if(weightTolerance <= 0) weightTolerance = 0;
        if(weightTolerance >= 50) weightTolerance = 50;
        showSetMenu(heading, String(weightTolerance, 1) + "g");
    }

    if(ButtonX.down) {
        showSetMenu(heading, "Cancel");
        delay(500);
        uiMode = MODE_MENU;
        return;
    }

    if(ButtonR.down) {
        showSetMenu(heading, "Save");
        saveConfig();
        delay(500);
        uiMode = MODE_MENU;
        return;
    }
}

void runBuzz() {
    showBuzz();
}

void runSetTime() {
    String heading = "";
    if(mainMenuSelection == SET_TIME) {
        heading = "Set Time";
    } else if(mainMenuSelection == SET_ALARM) {
        heading = "Set Alarm";
    }
    //in the home position, either X or R returns to the main menu
    if(timePosition == 0) {
        if(ButtonX.down || ButtonR.down) {
            uiMode = MODE_MENU;
            return;
        }
    } 
    
    //if we're not setting, navigate between the things we can set,
    //and enter one if the position isn't zero
    if(!timeSetting) {
        if(encoder > 0 && timePosition < 3) timePosition++;
        else if(encoder < 0 && timePosition > 0) timePosition--;

        if(ButtonR.down) {
            timeSetting = true;
        }
        if(ButtonX.down) {
            uiMode = MODE_MENU;
            return;
        }

        showTimeMenu(heading, getTimeString(newTimeHour, newTimeMinute, 0, false, true), timePosition, timeSetting);
    } else {
        //set hour or minute depending on position
        if(timePosition == 1) {
            if(encoder != 0) {
                newTimeHour += encoder;
                if(newTimeHour < 0) newTimeHour = 23;
                if(newTimeHour > 23) newTimeHour = 0;
            }
            showTimeMenu(heading, getTimeString(newTimeHour, newTimeMinute, 0, false, true), timePosition, timeSetting);
        } else if(timePosition == 2) {
            if(encoder != 0) {
                newTimeMinute += encoder * (mainMenuSelection == SET_TIME ? 1 : 5);
                if(newTimeMinute < 0) newTimeMinute = 55;
                if(newTimeMinute > 55) newTimeMinute = 0;
            }
            showTimeMenu(heading, getTimeString(newTimeHour, newTimeMinute, 0, false, true), timePosition, timeSetting);
        } else if(timePosition == 3) {
            if(encoder != 0) {
                newTimeHour = (newTimeHour + 12) % 24;
            }
            showTimeMenu(heading, getTimeString(newTimeHour, newTimeMinute, 0, false, true), timePosition, timeSetting);
        }

        //save or cancel on button push
        if(ButtonR.down) {
            showTimeMenu(heading, "  Save  ", 0, false);

            //If setting the time, we actually set the RTC chip's time
            //Otherwise it's just a config save
            if(mainMenuSelection == SET_TIME) {
                rtc.set((uint8_t)newTimeHour, (uint8_t)newTimeMinute);
            } else if(mainMenuSelection == SET_ALARM) {
                alarmHour = newTimeHour;
                alarmMinute = newTimeMinute;
                saveConfig();
            }
            delay(500);
            timeSetting = false;
            timePosition = 0;
            showTimeMenu(heading, getTimeString(newTimeHour, newTimeMinute, 0, false, true), timePosition, timeSetting);
        }
        if(ButtonX.down) {
            showTimeMenu(heading, " Cancel ", 0, false);

            //Apply the values that we started with - either from the RTC or from the config
            if(mainMenuSelection == SET_TIME) {
                newTimeHour = (int)rtc.hour;
                newTimeMinute = (int)rtc.minute;
            } else if(mainMenuSelection == SET_ALARM) {
                newTimeHour = alarmHour;
                newTimeMinute = alarmMinute;
                saveConfig();
            }
            delay(500);
            timeSetting = false;
            timePosition = 0;
            showTimeMenu(heading, getTimeString(newTimeHour, newTimeMinute, 0, false, true), timePosition, timeSetting);
        }
    }
}

void runAutoCalibrate(float calibrationWeight) {
    display.clearDisplay();
    drawText("Calibrate:", 2, 0, 0);
    display.display();

    long startCalibrationFactor = calibrationFactor;

    //Set everything up for auto-calibration
    calibrationFactor = 100;
    scale.scale.set_scale(calibrationFactor);
    scale.updateMass(3);

    float offset = 8192;
    float delta = scale.massG - calibrationWeight;
    float lastDelta = delta;

    //work out initial direction - up or down
    calibrationFactor += offset;
    scale.scale.set_scale(calibrationFactor);
    scale.updateMass(3);
    if(scale.massG < 0) {
        calibrationFactor = -8292;
        offset = -8192;
        delta = scale.massG - calibrationWeight;
        lastDelta = delta;
    }
    display.clearDisplay();
    drawText("Calibrate:", 2, 0, 0);
    drawText("c: " + String(calibrationFactor), 1, 0, 30);
    drawText("o: " + String(offset), 1, 0, 40);
    drawText("m: " + String(scale.massG), 1, 0, 50);
    display.display();

    int attempts = 0;
    int successCount = 0;
    while (abs(offset) > 1) {
        timeTick();
        loopInputs();

        //cancel if they hold the A button down
        if(ButtonX.is) {
            attempts = 100;
            break;
        }

        calibrationFactor += offset;
        scale.scale.set_scale(calibrationFactor);
        scale.updateMass(3);

        delta = scale.massG - calibrationWeight;
        
        display.clearDisplay();
        drawText("Calibrate:", 2, 0, 0);
        //logarithm because we divide offset as we approach the correct calibration weight
        float progress = 1.0 - min(1.0, max(0.0, ((log(abs(offset)) / log(2)) + 1) / 14.0));
        int barWidth = (int)round((DISPLAY_WIDTH - 4) * progress);
        display.drawRect(0, 16, DISPLAY_WIDTH, 10, WHITE);
        display.fillRect(2, 17, barWidth, 8, WHITE);
        drawText("c: " + String(calibrationFactor), 1, 0, 30);
        drawText("o: " + String(offset), 1, 0, 40);
        drawText("m: " + String(scale.massG), 1, 0, 50);
        display.display();

        //if we have successes, then we hold calibration factor to make sure that it didn't just jitter to a good spot
        if(successCount == 0) {
            //we've overshot the correct value
            if ((delta > 0) != (lastDelta > 0)) {
                if (abs(delta) > abs(lastDelta)) {
                    //we overshot by a lot, go back!
                    calibrationFactor -= offset;
                    offset *= 0.5;
                } else {
                    //we overshot by a little, switch directions
                    offset *= -0.5;
                }
            } else if (abs(delta) > abs(lastDelta)) {
                //we're going the wrong way, turn around!
                offset *= -1;
            }
        }

        //if we're spot on, start counting up - we want to get three consecutive 'hits'
        if (abs(delta) < 0.01) {
            successCount++;
        } else {
            successCount = 0;
        }

        //the calibration is stable and good - we can end early, hooray!
        if(successCount > 3) {
            break;
        }

        //If something prevents us from calibrating successfully, finish here
        if (attempts >= 100) {
            break;
        }

        lastDelta = delta;
        attempts++;
    }

    display.clearDisplay();

    //if we didn't get a good calibration factor, report the failure and reset to the old calibration factor
    //note that if we're off by less than 50mg, we can still consider that a win, I reckon
    if (attempts >= 100 && abs(delta) > 0.05) {
        drawText("Calibrate", 2, 0, 0);
        drawText("Failed!", 2, 0, 16);
        calibrationFactor = startCalibrationFactor;
        scale.scale.set_scale(calibrationFactor);
    } else {
        drawText("Calibrate", 2, 0, 0);
        drawText("Success!", 2, 0, 16);
        saveConfig();
    }
    display.display();
    delay(2000);
    display.clearDisplay();
}
