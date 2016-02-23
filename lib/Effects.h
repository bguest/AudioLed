#ifndef EFFECTS_H
#define EFFECTS_H

#define DATA_PIN 11
#define CLK_PIN 13

#define USE_LINE_SPECTRUM 1
//#define USE_SINGLE_FADE

#include "effects/Effect.h"
#include "effects/Diffusion.h"
#include "effects/RandomOn.h"
#include "effects/TwoColor.h"
#ifdef USE_SINGLE_FADE
  #include "effects/SingleFade.h"
#endif
#include "effects/Spectrum0.h"
#include "effects/Wander.h"
#include "effects/Wave0.h"
#ifdef USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.h"
#endif
#include "effects/CenterPulse.h"

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
  CENTER_PULSE,

#ifdef USE_SINGLE_FADE
  SINGLE_FADE,
#endif
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
    void reset();
    void nextEffect(uint8_t layer);
    void prevEffect(uint8_t layer);

  private:
    unsigned long lastRun;
    unsigned long lastStep;
    void updateShouldStep(EffectData &data);

    Sign sign;

    void setEffect(uint8_t kEffect, uint8_t layer);
#ifdef DEBUG
    void printEffect(uint8_t kEffect);
#endif
    uint8_t cEffect[LAYER_COUNT];
    Effect* effect[LAYER_COUNT];

    RandomOn randomOn;
  #ifdef USE_SINGLE_FADE
    SingleFade singleFade;
  #endif
    TwoColor twoColor;
    Diffusion diffusion;
    Spectrum0 spectrum0;

  #ifdef USE_LINE_SPECTRUM
    SpectrumLine spectrumLine;
  #endif
    CenterPulse centerPulse;

    Wander wander;
    Wave0 wave0;

    Adafruit_WS2801 strip;

    void updateStrip();
};
#endif

