#pragma once
#include <Arduino.h>
#include "StaffEffect.h"

#define ANIM_COUNT  3

enum UIAnimation {
    LOAD_EFFECT = 0,
    DEMO_EFFECT = 1,
    MANUAL_EFFECT = 2
};

class UI {
public:
    UI(CRGB* leds, uint16_t numLeds, uint8_t* toShow);

    void update();

private:
    StaffEffect* anim[3];

    uint8_t* toShowUI;
    short idx;
    bool bPlay = false;
    StaffEffect* nowEffect;

    unsigned long startShow;
    unsigned long endShow;

    CRGB* leds;
    uint16_t numLeds;
};
