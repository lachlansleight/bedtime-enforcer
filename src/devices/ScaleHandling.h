#ifndef _SCALEHANDLING_H
#define _SCALEHANDLING_H

#include <Arduino.h>
#include <HX711.h>

#include "../menu/DisplayHandling.h"

#include "../lib/config.h"
#include "../lib/consts.h"

class Scale {
    public:
        Scale();
        float massG;
        HX711 scale;
        bool calibrated;
        void setupScale();
        void updateMass(int samples);
        void tare();
};

extern Scale scale;

#endif