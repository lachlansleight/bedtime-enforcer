#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "../lib/consts.h"

class Buzzer {
    public:
        Buzzer();
        void initialize(int p, int freq);
        int pin;
        int frequency;
        bool is;
        void on();
        void on(int freq);
        void off();
};

extern Buzzer buzzer;

#endif