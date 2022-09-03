#ifndef _MENUDISPLAY_H
#define _MENUDISPLAY_H

#include <Arduino.h>
#include "../lib/consts.h"
#include "./DisplayHandling.h"


void showInitMessage(String message);
void showHomeScreen(String timeString, float massG);
void showMainMenu(int selected);
void showSetMenu(String heading, String value);
void showTimeMenu(String heading, String timeString, int position, bool setting);
void showBuzz();
void showTare();
void showTune(int freq);
void displayDebug(bool ButtonR, bool ButtonX, int encoderPos, float massG, String time);
String getButtonDebugString(String prefix, bool is);

#endif