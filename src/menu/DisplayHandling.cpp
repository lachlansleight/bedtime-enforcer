#include "./DisplayHandling.h"

Adafruit_SH1106 display(PIN_SCR_SDA, PIN_SCR_SCL);

//for debug mode display
int count = 0;

void setupDisplay()
{
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    display.setTextWrap(0);
    display.setTextColor(WHITE);
    display.setTextSize(1);
}

void drawText(String message, byte textSize, int cursorX, int cursorY)
{
    display.setTextSize(textSize);
    display.setCursor(cursorX, cursorY);
    display.println(message);
}

void drawCenterText(String message, byte textSize, int cursorY)
{
    display.setTextSize(textSize);
    byte length = message.length();
    byte remainder = DISPLAY_WIDTH - (length * 6 * textSize);
    display.setCursor(remainder / 2, cursorY);
    display.print(message);
}

void drawRightText(String message, byte textSize, int cursorY)
{
    display.setTextSize(textSize);
    byte length = message.length();
    byte remainder = DISPLAY_WIDTH - (length * 6 * textSize);
    display.setCursor(remainder, cursorY);
    display.print(message);
}