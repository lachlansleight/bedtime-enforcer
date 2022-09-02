#include "RTC.h"

Ds1302 ds1302(PIN_CLK_CE, PIN_CLK_SCK, PIN_CLK_DAT);
RTC rtc = RTC();

RTC::RTC()
{

}

void RTC::begin(int h, int m)
{
    ds1302.init();
    Ds1302::DateTime dt = {
        .year = 22,
        .month = Ds1302::MONTH_AUG,
        .day = 26,
        .hour = hour,
        .minute = minute,
        .second = 0,
        .dow = Ds1302::DOW_FRI
    };
    ds1302.setDateTime(&dt);
    hour = h;
    minute = m;
}

void RTC::update()
{
    Ds1302::DateTime now;
    ds1302.getDateTime(&now);
    hour = now.hour;
    minute = now.minute;
    second = now.second;
}

String RTC::getTimeString(bool withSecond) {
    String outp = getTimePieceString(hour) + ":" + getTimePieceString(minute);
    if(withSecond) outp += ":" + getTimePieceString(second);
    return outp;
}

String RTC::getTimePieceString(int val)
{
    if(val == 0) return "00";
    if(val < 10) return "0" + String(val);
    return String(val);
}