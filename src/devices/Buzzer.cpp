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
    if(is) return;
    ledcWriteTone(1, frequency);
    is = true;
}

void Buzzer::on(int freq)
{
    if(is) return;
    ledcWriteTone(1, freq);
    is = true;
}

void Buzzer::off()
{
    if(!is) return;
    ledcWrite(1, 0);
    is = false;
}