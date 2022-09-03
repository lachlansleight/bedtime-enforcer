#include "RTC.h"

Ds1302 ds1302(PIN_CLK_CE, PIN_CLK_SCK, PIN_CLK_DAT);
RTC rtc = RTC();

RTC::RTC()
{

}

void RTC::begin()
{
    ds1302.init();
    delay(500);
}

void RTC::begin(int h, int m)
{
    ds1302.init();
    delay(500);
    set(h, m);
}

void RTC::set(int h, int m)
{
    Ds1302::DateTime dt;
    dt.year = 22;
    dt.month = Ds1302::MONTH_AUG;
    dt.day = 26;
    dt.hour = h % 24;
    dt.minute = m % 60;
    dt.second = 0;
    dt.dow = Ds1302::DOW_FRI;
    ds1302.setDateTime(&dt);
    hour = h;
    minute = m;
}

void RTC::update()
{
    Ds1302::DateTime now;
    ds1302.getDateTime(&now);
    hour = (int)now.hour;
    minute = (int)now.minute;
    second = (int)now.second;
}

String RTC::getString(bool withSecond, bool withColon) {
    return getTimeString(hour, minute, second, withSecond, withColon);
}

String getTimeString(int hour, int minute, int second, bool withSecond, bool withColon) {
    String outp = getTimePieceString((hour == 12 || hour == 0) ? 12 : hour % 12) + (withColon ? ":" : " ") + getTimePieceString(minute);
    if(withSecond) outp += ":" + getTimePieceString(second);
    if(hour < 12) outp += " AM";
    else outp += " PM";
    return outp;
}

String getTimePieceString(int val)
{
    if(val == 0) return "00";
    if(val < 10) return "0" + String(val);
    return String(val);
}