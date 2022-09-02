#include "./MenuDisplay.h"


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

void displayDebug(bool buttonR, bool buttonX, int encoderPos, float massG, String time)
{
    display.clearDisplay();

    String lineA = "";
    lineA += getButtonDebugString("R", buttonR);
    lineA += getButtonDebugString(" X", buttonX);
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