#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "StaffEffect.h"

class LoadAnim : public StaffEffect {
private:
    CRGB* leds;
    int num_leds;

    unsigned long startTime;
    const float effectDuration = 1500.0; // move
    const float fadeDuration = 500.0;    // ret br.
    bool started = false;

    const byte maxWhite = 200; // ~80%
    int trailLength;

    CRGB* ledsTarget;

public:
    void begin(CRGB* _leds, int _num_leds) override {
        leds = _leds;
        num_leds = _num_leds;
        trailLength = num_leds / 4;

        ledsTarget = new CRGB[num_leds];

        for (int i = 0; i < num_leds; i++) {
            leds[i] = CRGB::Black;
            ledsTarget[i] = CRGB::Black;
        }

        startTime = millis();
        started = true;
    }

    void update(uint16_t value) override {
        if (!started) return;

        unsigned long now = millis();
        unsigned long elapsed = now - startTime;

        if (elapsed <= effectDuration) {
            float p = float(elapsed) / effectDuration; // 0..1
            float pos = p * (num_leds - 1);

            for (int i = 0; i < num_leds; i++) {
                float dist = i - pos;
                if (dist >= 0 && dist < trailLength) {
                    float factor = 1.0 - (dist / trailLength); // 1..0
                    byte brightness = uint8_t(maxWhite * factor);
                    leds[i] = CRGB(brightness, brightness, brightness);
                    ledsTarget[i] = leds[i]; // for fade
                } else {
                    leds[i] = CRGB::Black;
                    ledsTarget[i] = CRGB::Black;
                }
            }

        } else if (elapsed <= effectDuration + fadeDuration) {
            float t = float(elapsed - effectDuration) / fadeDuration; // 0..1

            for (int i = 0; i < num_leds; i++) {
                leds[i].r = uint8_t(ledsTarget[i].r * t);
                leds[i].g = uint8_t(ledsTarget[i].g * t);
                leds[i].b = uint8_t(ledsTarget[i].b * t);
            }

        } else {
            started = false;
        }
    }

    unsigned long getTime() override {
        return effectDuration + fadeDuration;
    }

    ~LoadAnim() {
        delete[] ledsTarget;
    }
};
