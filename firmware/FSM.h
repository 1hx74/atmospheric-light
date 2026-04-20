#pragma once
#include <Arduino.h>
#include "Input.h"
#include "EffectSequence.h"

#define DEMO_INTERVAL   30000

enum FSMState {
    LOAD,
    AUTO,
    MANUAL,
    DEMO
};

class FSM {
public:
    FSM(InputState* state, EffectSequence& seq, Effect*& currentEffect, CRGB* leds, uint16_t numLeds, uint8_t* toShowUI);

    void update();
    FSMState getState() const;
    void setState(FSMState newState);

private:
    FSMState fsmState;

    InputState* state;
    EffectSequence& effectSequence;
    Effect*& nowEffect;
    CRGB* leds;
    uint16_t numLeds;
    uint8_t* toShowUI;

    unsigned long demoLastSwitch = 0;
};
