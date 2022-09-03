#include "config.h"

Preferences preferences;

bool configSet = false;
long calibrationFactor = -36052;
float weight = 195.0;
float weightTolerance = 20.0;

int alarmHour = 23;
int alarmMinute = 45;

int buzzerFreq = 2532;
int alarmPeriod = 120;

void initializeConfig()
{
    //sensible defaults
    calibrationFactor = -36052;
    
    preferences.begin("bedtime", false); 

    //if this value isn't 128, it means this is literally the first time
    //the device has been turned on, so we initialize the EEPROM
    configSet = preferences.getBool("configSet", false);
    if(!configSet) {
        saveConfig();
        return;
    }

    //Get everything else from the EEPROM
    calibrationFactor = preferences.getLong("calFactor", -36052);
    weight = preferences.getFloat("weight", 195);
    weightTolerance = preferences.getFloat("weightTolerance", 20);
    alarmHour = preferences.getInt("alarmHour", 23);
    alarmMinute = preferences.getInt("alarmMinute", 45);
    buzzerFreq = preferences.getInt("buzzerFreq", 2532);
    alarmPeriod = preferences.getInt("alarmPeriod", 120);
    
    preferences.end();
}

void saveConfig()
{
    preferences.begin("bedtime", false); 
    configSet = true;
    preferences.putBool("configSet", configSet);
    preferences.putLong("calFactor", calibrationFactor);
    preferences.putFloat("weight", weight);
    preferences.putFloat("weightTolerance", weightTolerance);
    preferences.putInt("alarmHour", alarmHour);
    preferences.putInt("alarmMinute", alarmMinute);
    preferences.putInt("buzzerFreq", buzzerFreq);
    preferences.putInt("alarmPeriod", alarmPeriod);
    
    preferences.end();
}