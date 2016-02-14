#ifndef EFFECTS_H
#define EFFECTS_H

#define LED_COUNT 35
#define DATA_PIN 11
#define CLK_PIN 13

#include "Arduino.h"
#include "Adafruit_WS2801.h"
#include "Sign.h"
#include "effects/Effect.h"
#include "effects/RandomOn.h"
#include "effects/SingleFade.h"
#include "effects/TwoColor.h"

typedef const enum _Layer {
  TextLayer = 0,
  ColorLayer,
  LayerCount
} Layer;

typedef const enum _EFFECTS{
  RANDOM_ON = 0,
  TEXT_EFFECT_COUNT,

  SINGLE_FADE,
  TWO_COLOR,
  COLOR_EFFECT_COUNT
} EFFECTS;

const uint8_t UPDATE_DURRATION = 5;

class Effects{
  public:
    Effects();
    void init();
    void run();
    void setEffect(uint8_t kEffect, Layer layer);
    void changeEffect();

  private:
    unsigned long lastRun;
    unsigned long lastStep;
    void updateShouldStep();

    Sign sign;

    uint8_t cEffect[LayerCount];
    Effect* effect[LayerCount];

    RandomOn randomOn;
    SingleFade singleFade;
    TwoColor twoColor;

    Adafruit_WS2801 strip;

    void updateStrip();

    EffectData data;
};
#endif

