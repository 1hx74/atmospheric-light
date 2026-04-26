#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "UI.h"

#include "LoadAnim.cpp"
#include "DemoAnim.cpp"
#include "ManualAnim.cpp"

UI::UI(CRGB* leds, uint16_t numLeds, uint8_t* toShowUI) :
       leds(leds),
       numLeds(numLeds),
       toShowUI(toShowUI)
{
    anim[0] = new LoadAnim();
    anim[1] = new DemoAnim();
    anim[2] = new ManualAnim();
}

void UI::update() {

    if (bPlay && nowEffect) {
        nowEffect->update(0);
        if (millis() - startShow > endShow) {
            toShowUI[idx] -= 1;
            bPlay = false;
        }
        return;
    }

    for (short i = 0; i < ANIM_COUNT; i++) {
        if (toShowUI[i] == 0) { continue; }

        if (!bPlay) {
            bPlay = true;
            idx = i;
            startShow = millis();
            nowEffect = anim[idx];
            endShow = nowEffect->getTime();
            nowEffect->begin(leds, numLeds, FastLED.getBrightness());
            break;
        }
    }
}