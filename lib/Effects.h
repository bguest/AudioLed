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
#include "effects/Wave0.h"
#ifdef USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.h"
#endif

#include "Adafruit_WS2801.h"

const uint8_t UPDATE_DURRATION = 5;

#define TEXT_LAYER 0
#define COLOR_LAYER 1
#define LAYER_COUNT 2

typedef const enum _EFFECTS {
  RANDOM_ON = 0,
  WANDER,
  SPECTRUM_0,
#ifdef USE_LINE_SPECTRUM
  SPECTRUM_LINE,
#endif

  SINGLE_FADE,
  TWO_COLOR,
  DIFFUSION,
  WAVE0,
  EFFECT_COUNT
} EFFECTS;


class Effects{
  public:
    Effects();
    void init();
    void run(EffectData &data);
    void push(IrInput input, uint8_t layer);
    void nextEffect(uint8_t layer);
    void prevEffect(uint8_t layer);

  private:
    unsigned long lastRun;
    unsigned long lastStep;
    void updateShouldStep(EffectData &data);

    Sign sign;

    void setEffect(uint8_t kEffect, uint8_t layer);
    uint8_t cEffect[LAYER_COUNT];
    Effect* effect[LAYER_COUNT];

    RandomOn randomOn;
    SingleFade singleFade;
    TwoColor twoColor;
    Diffusion diffusion;
    Spectrum0 spectrum0;

  #ifdef USE_LINE_SPECTRUM
    SpectrumLine spectrumLine;
  #endif

    Wander wander;
    Wave0 wave0;

    Adafruit_WS2801 strip;

    void updateStrip();
};
#endif

