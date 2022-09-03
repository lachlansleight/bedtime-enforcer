#ifndef _INPUTHANDLING_H
#define _INPUTHANDLING_H

#include <Arduino.h>
#include <ButtonDebounce.h>
#include <RotaryEncoder.h>

#include "../lib/consts.h"
#include "../lib/Button.h"
#include "../lib/TimeHandling.h"

#define DEBOUNCE_TIME 50

extern RotaryEncoder encoderHandler;

extern int encoder;
extern int encoderPos;
extern Button ButtonR;
extern Button ButtonX;

void setupInputs();
void resetInputs();
void loopInputs();
void buttonChangedR(int state);
void buttonChangedX(int state);

#endif