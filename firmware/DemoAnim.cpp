#pragma once
#include "StaffEffect.h"

class DemoAnim : public StaffEffect {
public:
    unsigned long getTime() override {
        return t_segment * segments + t_restore + t_prepare + 600;
    }

protected:
    static const int segments = 5;

    const unsigned long t_segment = 200;
    const unsigned long t_fade = 300;
    const byte maxWhite = 200;

    unsigned long animStart = 0;

    void onBegin() override {
        animStart = 0;
    }

    void processing(State &stateRef, CRGB* arr) override {
        unsigned long now = millis();

        if (animStart == 0) {
            animStart = now;
        }

        unsigned long elapsed = now - animStart;

        int segment_len = num_leds / segments;
        if (segment_len <= 0) return;

        unsigned long totalDuration = t_segment * segments;

        if (elapsed >= totalDuration) {
            animStart = 0;
            stateRef = END;
            return;
        }

        int activeSeg = elapsed / t_segment;
        unsigned long segElapsed = elapsed % t_segment;

        for (int i = 0; i < num_leds; i++) {
            arr[i] = CRGB::Black;
        }

        for (int seg = 0; seg < segments; seg++) {
            float brightness = 0.0f;

            if (seg == activeSeg) {
                float t = (float)segElapsed / t_fade;
                t = fl::clamp(t, 0.0f, 1.0f);
                brightness = maxWhite * (1.0f - t);
            } 
            else if (seg == activeSeg - 1) {
                unsigned long prevElapsed = segElapsed + t_segment;
                float t = (float)prevElapsed / t_fade;
                t = fl::clamp(t, 0.0f, 1.0f);
                brightness = maxWhite * (1.0f - t);
            }

            byte b = (byte)brightness;

            for (int i = 0; i < segment_len; i++) {
                int idx = seg * segment_len + i;
                if (idx < num_leds) {
                    arr[idx] = CRGB(b, b, b);
                }
            }
        }
    }
};