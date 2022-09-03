#ifndef DS1302_H
#define DS1302_H

#include <Arduino.h>
#include <Ds1302.h>
#include "../lib/consts.h"

class RTC {
    public:
        RTC();
        void begin();
        void begin(int hour, int minute);
        void set(int hour, int minute);
        void update();
        String getString(bool withSecond, bool withColon);
        int hour;
        int minute;
        int second;
};

String getTimeString(int hour, int minute, int second, bool withSecond, bool withColon);
String getTimePieceString(int val);

extern Ds1302 ds1302;
extern RTC rtc;

#endif