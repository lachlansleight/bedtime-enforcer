#ifndef _DISPLAYHANDLING_H
#define _DISPLAYHANDLING_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h> //https://github.com/wonho-maker/Adafruit_SH1106
#include <Wire.h>

#include "./InputHandling.h"
#include "../devices/ScaleHandling.h"

#include "../lib/consts.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

extern Adafruit_SH1106 display;

void setupDisplay();
void drawText(String message, byte textSize, int cursorX, int cursorY);
void drawCenterText(String message, byte textSize, int cursorY);
void drawRightText(String message, byte textSize, int cursorY);

#endif