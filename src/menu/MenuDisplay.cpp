#include "./MenuDisplay.h"

//https://rickkas7.github.io/DisplayGenerator/index.html


void showInitMessage(String message)
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    drawCenterText("Bedtime", 2, 10);
    drawCenterText("v" + String(MAJOR_VERSION) + "." + String(MINOR_VERSION) + "." + String(PATCH_VERSION), 1, 30);
    if (message.length() > 0) {
        drawCenterText(message, 1, 55);
    }
    display.display();
}

void showHomeScreen(String time, float massG) {
    display.clearDisplay();

    drawCenterText(time, 2, 24);
    //draw text, if necessary
    if(massG > 5) drawCenterText(String(massG, 1) + "g", 1, 48);

    display.display();
}

void showMainMenu(int selected) {
    display.clearDisplay();

    if(selected == 0) {
        display.setTextColor(BLACK, WHITE);
        display.fillRect(0, 0, 128, 12, WHITE);
    }
    drawText("Set Time", 1, 4, 2);
    display.setTextColor(WHITE);

    if(selected == 1) {
        display.setTextColor(BLACK, WHITE);
        display.fillRect(0, 12, 128, 12, WHITE);
    }
    drawText("Set Alarm", 1, 4, 14);
    display.setTextColor(WHITE);

    if(selected == 2) {
        display.setTextColor(BLACK, WHITE);
        display.fillRect(0, 24, 128, 12, WHITE);
    }
    drawText("Set Weight", 1, 4, 26);
    display.setTextColor(WHITE);

    if(selected == 3) {
        display.setTextColor(BLACK, WHITE);
        display.fillRect(0, 36, 128, 12, WHITE);
    }
    drawText("Set Tolerance", 1, 4, 38);
    display.setTextColor(WHITE);

    if(selected == 4) {
        display.setTextColor(BLACK, WHITE);
        display.fillRect(0, 48, 128, 12, WHITE);
    }
    drawText("Calibrate Scale", 1, 4, 50);
    display.setTextColor(WHITE);

    display.display();
}

void showSetMenu(String heading, String value) {
    display.clearDisplay();

    //header
    display.drawLine(0, 8, 128, 8, WHITE);
    drawCenterText(heading, 1, 0);

    //footer
    display.drawLine(0, 54, 128, 54, WHITE);
    drawText("X: Cancel", 1, 0, 56);
    drawRightText("R: Confirm", 1, 56);

    //arrows and value
    display.fillTriangle(5, 32, 10, 37, 10, 27, WHITE);
    display.drawLine(10, 32, 15, 32, WHITE);
    display.fillTriangle(123, 32, 118, 37, 118, 27, WHITE);
    display.drawLine(118, 32, 113, 32, WHITE);
    drawCenterText(value, 2, 24);

    display.display();
}

void showTimeMenu(String heading, String timeString, int position, bool setting) {
    display.clearDisplay();

    //header
    display.drawLine(0, 8, 128, 8, WHITE);
    drawCenterText(heading, 1, 0);

    //footer
    display.drawLine(0, 54, 128, 54, WHITE);
    if(setting) {
        if(position == 0) {
            drawText("X: Back", 1, 0, 56);
        } else {
            drawText("X: Cancel", 1, 0, 56);
            drawRightText("R: Confirm", 1, 56);
        }
    } else {
        drawText("X: Back", 1, 0, 56);
        drawRightText("R: Set", 1, 56);
    }
    
    //center
    display.setCursor(18, 24);
    display.setTextSize(2);
    display.println(timeString);

    //underline current target time portion
    if(position == 1) {
        display.drawLine(17, 40, 40, 40, WHITE);
    } else if(position == 2) {
        display.drawLine(54, 40, 76, 40, WHITE);
    } else if(position == 3) {
        display.drawLine(88, 40, 114, 40, 1);
    }

    display.display();
}

void showTare() {
    display.clearDisplay();
    drawCenterText("Scale", 2, 10);
    drawCenterText("Tared", 2, 30);
    display.display();
}

void showBuzz() {
    display.clearDisplay();
    if((millis() / 1000) % 2 == 1) {
        display.setTextColor(BLACK, WHITE);
        display.fillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, WHITE);
    } else {
        display.setTextColor(WHITE);
    }
    drawCenterText("GO TO", 3, 10);
    drawCenterText("BED", 3, 35);
    display.display();

    display.setTextColor(WHITE);
}

void showTune(int freq) {
    display.clearDisplay();
    drawCenterText("Tuning", 2, 10);
    drawCenterText(String(freq) + "Hz", 2, 30);
    display.display();
}

void displayDebug(bool ButtonR, bool ButtonX, int encoderPos, float massG, String time)
{
    display.clearDisplay();

    String lineA = "";
    lineA += getButtonDebugString("R", ButtonR);
    lineA += getButtonDebugString(" X", ButtonX);
    drawText(lineA, 1, 0, 0);

    drawText(time, 1, DISPLAY_WIDTH * 0.5, 0);

    drawText("Enc " + String(encoderPos), 1, 0, 16);
    drawText("Scl " + String(massG, 1) + "g", 1, DISPLAY_WIDTH * 0.5, 16);

    display.display();
}

String getButtonDebugString(String prefix, bool is)
{
    String output = prefix + "|";
    if(is) output += "#";
    else output += " ";
    output += "|";
    return output;
}