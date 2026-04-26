#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <math.h>
#include "StaffEffect.h"

class LoadAnim : public StaffEffect {
private:
    unsigned long startTime = 0;

    const float t_run = 1500.0f;
    const byte maxWhite = 200;
    int trailLength = 0;
    unsigned long t_restore = 600;

public:
    unsigned long getTime() override {
        return (unsigned long)(t_run) + t_restore + 100;
    }

protected:
    void prepare(State &stateRef, CRGB* arr) override {
        trailLength = num_leds / 4;
        startTime = millis();
        stateRef = RUN;
    }

    void processing(State &stateRef, CRGB* arr) override {
        unsigned long elapsed = millis() - startTime;
        float t = float(elapsed) / t_run;

        if (t >= 1.0f) {
            stateRef = END;
            return;
        }

        float pos = t * (num_leds - 1);

        for (int i = 0; i < num_leds; i++) {
            float dist = i - pos;
            if (dist >= 0 && dist < trailLength) {
                float factor = 1.0f - (dist / trailLength);
                byte brightness = uint8_t(maxWhite * factor);
                arr[i] = CRGB(brightness, brightness, brightness);
            } else {
                arr[i] = CRGB::Black;
            }
        }
    }

    void onBegin() override {
        startTime = 0;
    }
};