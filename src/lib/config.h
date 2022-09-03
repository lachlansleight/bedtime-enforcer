#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

extern Preferences preferences;

//controlled automatically
extern bool configSet;

//set by the auto-calibrator
extern long calibrationFactor;

//set explicitly by user using the menu
extern float weight;
extern float weightTolerance;
extern int alarmHour;
extern int alarmMinute;

//set at compile time
extern int buzzerFreq;
extern int alarmPeriod;

void initializeConfig();
void saveConfig();

#endif