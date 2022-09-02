#include "./ScaleHandling.h"

Scale scale = Scale();

Scale::Scale()
{
    
}

void Scale::setupScale()
{
    scale.begin(PIN_SCL_DAT, PIN_SCL_SCK);
    scale.set_scale(calibrationFactor);
    scale.tare();
    delay(500);
}

void Scale::updateMass(int samples)
{
    massG = scale.get_units(samples) * 50.0;
}

void Scale::tare()
{
    scale.tare();
}