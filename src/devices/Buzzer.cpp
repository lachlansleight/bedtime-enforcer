#include "Buzzer.h"

Buzzer buzzer = Buzzer();

Buzzer::Buzzer()
{
    pin = -1;
    frequency = 0;
    is = false;
}

void Buzzer::initialize(int p, int freq)
{
    pin = p;
    frequency = freq;
    ledcAttachPin(pin, 1);
    is = false;
}

void Buzzer::on()
{
    ledcWriteTone(1, frequency);
    is = true;
}

void Buzzer::off()
{
    ledcWrite(1, 0);
    is = false;
}