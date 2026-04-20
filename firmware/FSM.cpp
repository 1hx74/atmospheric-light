#include "FSM.h"
#include "UI.h"

FSM::FSM(InputState* state, EffectSequence& effectSequence, Effect*& nowEffect, CRGB* leds, uint16_t NUM_LEDS, uint8_t* toShowUI)
    : fsmState(LOAD),
      state(state),
      effectSequence(effectSequence),
      nowEffect(nowEffect),
      leds(leds),
      numLeds(NUM_LEDS),
      toShowUI(toShowUI)
{}

FSMState FSM::getState() const {
    return fsmState;
}

void FSM::setState(FSMState newState) {
    fsmState = newState;
}

void FSM::update() {
    if (!state) return;

    uint16_t knobValue = state->knobAngle;

    switch (fsmState) {

        case LOAD:
            // todo begin anim. and block click
            nowEffect = effectSequence.current();
            nowEffect->begin(leds, numLeds);
            toShowUI[static_cast<int>(UIAnimation::LOAD_EFFECT)] += 1;
            setState(MANUAL);
            break;

        case AUTO:
            // todo auto
            break;

        case MANUAL:
            if (state->buttonClick) {
                nowEffect = effectSequence.next();
                nowEffect->begin(leds, numLeds);
            } 
            else if (state->buttonDoubleClick) {
                nowEffect = effectSequence.prev();
                nowEffect->begin(leds, numLeds);
            } 
            else if (state->buttonLongPress) {
                // todo -> add/rm fav.
            }
            else if (state->buttonLongLongPress) {
                demoLastSwitch = millis();
                setState(DEMO);
                toShowUI[static_cast<int>(UIAnimation::DEMO_EFFECT)] += 1;
            }

            nowEffect->update(knobValue);
            break;

        case DEMO: 
            unsigned long now = millis();

            if (state->buttonClick || state->buttonDoubleClick) {
                setState(MANUAL);
                toShowUI[static_cast<int>(UIAnimation::MANUAL_EFFECT)] += 1;
                break;
            }

            if (now - demoLastSwitch >= DEMO_INTERVAL) {
                demoLastSwitch = now;
                
                nowEffect = effectSequence.next();
                nowEffect->begin(leds, numLeds);
            }

            nowEffect->update(knobValue);

            break;
    }
}
