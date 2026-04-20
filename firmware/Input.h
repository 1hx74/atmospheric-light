#pragma once
#include <Arduino.h>
#include "InputState.h"

#define LONGPRESS_MS       2000
#define DOUBLECLICK_MS     400
#define FILTER_ALPHA       0.4f
#define DEBOUNCE_MS 30

enum ButtonState {
    IDLE,
    PRESS,
    LONG,
    RELEASE,
    CLICK_CHECK
};

class Input {
public:
    Input(InputState* outState, int buttonPin, int knobPin, int lightPin);
    void begin();
    void update();

private:
    int buttonPin;
    int knobPin;
    int lightPin;

    InputState state;
    InputState* outState;

    ButtonState btnState;
    unsigned long pressStartTime;
    unsigned long lastClickTime;
    int clickCount;

    float filteredKnob;
    float filteredLight;

    bool lastRawButton;
    unsigned long lastDebounceTime;
    bool readButton();
};