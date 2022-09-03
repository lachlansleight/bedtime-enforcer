#ifndef _MENUCONTROL_H
#define _MENUCONTROL_H

#include <Arduino.h>

#include "../lib/config.h"
#include "./MenuDisplay.h"

#include "./InputHandling.h"
#include "../devices/RTC.h"
#include "../devices/ScaleHandling.h"

//mode enum
#define MODE_HOME 0
#define MODE_MENU 1
#define MODE_SET 2
#define MODE_TIME 3
#define MODE_BUZZ 4
#define MODE_TUNE 5

//main menu enum
#define SET_TIME 0
#define SET_ALARM 1
#define SET_WEIGHT 2
#define SET_TOLERANCE 3
#define SET_CALIBRATION 4

extern int uiMode;
extern int mainMenuSelection;

extern int newTimeHour;
extern int newTimeMinute;
extern int timePosition;
extern bool timeSetting;

void runUi();
void runHome();
void runMenu();
void runSet();
void runSetTime();
void runBuzz();
void runAutoCalibrate(float calibrationWeight);

#endif