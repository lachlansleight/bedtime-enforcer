#ifndef _MENUDISPLAY_H
#define _MENUDISPLAY_H

#include <Arduino.h>
#include "./DisplayHandling.h"

#include "../lib/consts.h"

void showInitMessage(String message);
void displayDebug(bool buttonR, bool buttonX, int encoderPos, float massG, String time);
String getButtonDebugString(String prefix, bool is);

#endif