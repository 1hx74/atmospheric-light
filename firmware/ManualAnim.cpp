#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "StaffEffect.h"

class ManualAnim : public StaffEffect {
private:
    CRGB* leds;
    int num_leds;

public:
    void begin(CRGB* _leds, int _num_leds) override {
        leds = _leds;
        num_leds = _num_leds;
    }

    void update(uint16_t value) override {
        for (int i = 0; i < num_leds; i++) {
            leds[i] = CRGB::Red;
        }
        FastLED.show();
    }

    unsigned long getTime() { return 1000; }
};
