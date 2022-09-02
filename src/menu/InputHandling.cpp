#include "./InputHandling.h"

RotaryEncoder encoderHandler(PIN_ROT_A, PIN_ROT_B, RotaryEncoder::LatchMode::FOUR3);

int encoder = 0;
int encoderPos = 0;

Button ButtonR(PIN_BTN_R, DEBOUNCE_TIME, buttonChangedR);
Button ButtonX(PIN_BTN_X, DEBOUNCE_TIME, buttonChangedX);

void IRAM_ATTR checkPosition()
{
  encoderHandler.tick();
}

void setupInputs()
{
    attachInterrupt(digitalPinToInterrupt(PIN_ROT_A), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ROT_B), checkPosition, CHANGE);
}

void resetInputs()
{
    encoder = 0;
    encoderPos = 0;

    ButtonR.reset();
    ButtonX.reset();
}

void loopInputs()
{
    ButtonR.update(deltaMillis);
    ButtonX.update(deltaMillis);
    //encoderHandler.tick();

    int newPos = encoderHandler.getPosition();
    if(encoderPos != newPos) {
        encoder = (int)encoderHandler.getDirection();
        encoderPos = newPos;
    } else {
        encoder = 0;
    }
}

void buttonChangedR(int state)
{
    ButtonR.buttonChanged(state);
}

void buttonChangedX(int state)
{
    ButtonX.buttonChanged(state);
}
