#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

extern Preferences preferences;

extern bool configSet;
extern long calibrationFactor;

void initializeConfig();
void saveConfig();

#endif