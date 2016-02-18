#ifndef EFFECTS_H
#define EFFECTS_H

#define DATA_PIN 11
#define CLK_PIN 13

#include "effects/Effect.h"
#include "effects/Diffusion.h"
#include "effects/RandomOn.h"
#include "effects/TwoColor.h"
#include "effects/SingleFade.h"
#include "effects/Spectrum0.h"
#include "effects/Wander.h"

#include "Adafruit_WS2801.h"

const uint8_t UPDATE_DURRATION = 5;

typedef const enum _Layer {
  TextLayer = 0,
  ColorLayer,
  LayerCount
} Layer;

typedef const enum _EFFECTS {
  RANDOM_ON = 0,
  SPECTRUM_0,
  WANDER,
  SINGLE_FADE,
  TWO_COLOR,
  DIFFUSION,
  EFFECT_COUNT
} EFFECTS;


class Effects{
  public:
    Effects();
    void init();
    void run(EffectData &data);
    void setEffect(uint8_t kEffect, Layer layer);
    void nextEffect(Layer layer);
    void prevEffect(Layer layer);

  private:
    unsigned long lastRun;
    unsigned long lastStep;
    void updateShouldStep(EffectData &data);

    Sign sign;

    uint8_t cEffect[LayerCount];
    Effect* effect[LayerCount];

    RandomOn randomOn;
    SingleFade singleFade;
    TwoColor twoColor;
    Diffusion diffusion;
    Spectrum0 spectrum0;
    Wander wander;

    Adafruit_WS2801 strip;

    void updateStrip();
};
#endif

