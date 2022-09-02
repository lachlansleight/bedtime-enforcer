#ifndef DS1302_H
#define DS1032

#include <Arduino.h>
#include <Ds1302.h>
#include "../lib/consts.h"

class RTC {
    public:
        RTC();
        void begin(int hour, int minute);
        void update();
        String getTimeString(bool withSecond);
        int hour;
        int minute;
        int second;
    private:
        String getTimePieceString(int val);
};

extern Ds1302 ds1302;
extern RTC rtc;

#endif