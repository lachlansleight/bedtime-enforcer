#include "TimeHandling.h"

int deltaMillis = 0;
long lastMillis = 0;

void timeTick()
{
    deltaMillis = int(millis() - lastMillis);
    lastMillis = millis();
}