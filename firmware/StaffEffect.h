#pragma once
#include "fl/clamp.h"
#include "fl/colorutils.h"
#include "Effect.h"
#include <Arduino.h>
#include <FastLED.h>

class StaffEffect : public Effect {
public:
    virtual unsigned long getTime() = 0;

    void begin(CRGB* _leds, int _num_leds, uint8_t _maxBrightness) {
        leds = _leds;
        num_leds = _num_leds;
        maxBrightness = _maxBrightness;
        restoreStart = 0;
        prepareStart = 0;
        state = START;
        onBegin();
    }

    void update(uint16_t value) override {
        switch (state) {
            case START:
                prepare(state, leds);
                break;
            case RUN:
                processing(state, leds);
                break;
            case END:
                restore(state, leds);
                break;
        }
    }

protected:
    CRGB* leds = nullptr;
    int num_leds = 0;

    enum State { START, RUN, END };
    State state = START;

    unsigned long t_prepare = 200;
    unsigned long prepareStart = 0;

    unsigned long t_restore = 200;
    unsigned long restoreStart = 0;

    uint8_t maxBrightness = 255;

    virtual void onBegin() {}

    virtual void prepare(State &stateRef, CRGB* arr) {
        if (prepareStart == 0) {
            prepareStart = millis();
        }
        float t = fl::clamp((float)(millis() - prepareStart) / t_prepare, 0.0f, 1.0f);
        uint8_t brightness = (uint8_t)(maxBrightness * (1.0f - t));
        
        FastLED.setBrightness(brightness);

        if (t >= 1.0f) {
            FastLED.setBrightness(maxBrightness);
            stateRef = RUN;
        }
    }


    virtual void processing(State &stateRef, CRGB* arr) = 0;

    void restore(State &stateRef, CRGB* arr) {
        if (restoreStart == 0) {
            restoreStart = millis();
        }
        float t = fl::clamp((float)(millis() - restoreStart) / t_restore, 0.0f, 1.0f);
        uint8_t brightness = (uint8_t)(maxBrightness * t);
        
        FastLED.setBrightness(brightness);

        if (t >= 1.0f) {
            FastLED.setBrightness(maxBrightness);
        }
    }
};