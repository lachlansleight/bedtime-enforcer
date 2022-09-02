#include "./MenuControl.h"

int uiMode = 0;
int mainMenuSelection = 0;

void runUi() {
    
}

void runAutoCalibrate() {
    display.clearDisplay();
    drawText("Calibrate:", 2, 0, 0);
    display.display();

    long startCalibrationFactor = calibrationFactor;

    //Set everything up for auto-calibration
    float calibrationWeight = 20;
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

        //cancel if they hold the X button down
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
