#include "config.h"

Preferences preferences;

bool configSet = false;
long calibrationFactor = -36052;

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
    
    preferences.end();
}

void saveConfig()
{
    preferences.begin("bedtime", false); 
    configSet = true;
    preferences.putBool("configSet", configSet);
    preferences.putLong("calFactor", calibrationFactor);
    
    preferences.end();
}