#pragma once
#include "StaffEffect.h"

class ManualAnim : public StaffEffect {
public:
    unsigned long getTime() override {
        return 1400;
    }

protected:

    unsigned long start = 0;

    void onBegin() override {
        start = millis();
    }

    void processing(State &stateRef, CRGB* arr) override {

        if (millis() >= start + 1000) {
            stateRef = END;
        }

        for (int i = 0; i < num_leds; i++) {
            arr[i] = CRGB::Red;
        }
    }
};