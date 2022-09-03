#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

extern Preferences preferences;

extern bool configSet;
extern long calibrationFactor;

extern float weight;
extern float weightTolerance;

extern int alarmHour;
extern int alarmMinute;

extern int buzzerFreq;

void initializeConfig();
void saveConfig();

#endif