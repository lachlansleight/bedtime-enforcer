#ifndef _MENUCONTROL_H
#define _MENUCONTROL_H

#include <Arduino.h>

#include "./InputHandling.h"
#include "./MenuDisplay.h"

#include "../devices/ScaleHandling.h"

#include "../lib/config.h"

extern int uiMode;
extern int mainMenuSelection;

void runUi();
void runAutoCalibrate();

#endif