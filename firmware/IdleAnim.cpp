#include "Effect.h"
#include <FastLED.h>

class IdleAnim : public Effect {
public:
    IdleAnim() : leds(nullptr), numLeds(0), lastMillis(0) {}

    void begin(CRGB* ledsArray, int num_leds) override {
        leds = ledsArray;
        numLeds = num_leds;
        lastMillis = millis();
    }

    void update(uint16_t value) override {
        
    }

private:
    CRGB* leds;
    int numLeds;
    unsigned long lastMillis;
    bool state;

    const uint8_t kpss[16] = {2, 1, 2, 0, 1, 2, 2, 1, 0, 1, 1, 1, 0, 1, 1, 1};
    int cur = 0;

};
