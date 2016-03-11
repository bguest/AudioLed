#ifndef EFFECTS_H
#define EFFECTS_H

#define DATA_PIN 11
#define CLK_PIN 13

#define USE_LINE_SPECTRUM
//#define USE_SINGLE_FADE
//#define USE_WANDER

#include "effects/Effect.h"
#include "effects/Diffusion.h"
#include "effects/RandomOn.h"
#include "effects/TwoColor.h"
#ifdef USE_SINGLE_FADE
  #include "effects/SingleFade.h"
#endif
#include "effects/Spectrum0.h"
#ifdef USE_WANDER
  #include "effects/Wander.h"
#endif
#include "effects/Wave0.h"
#ifdef USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.h"
#endif
#include "effects/CenterPulse.h"
#include "effects/TimeDomain.h"

#include "Adafruit_WS2801.h"

const uint8_t UPDATE_DURRATION = 5;

#define TEXT_LAYER 0
#define COLOR_LAYER 1
#define ADJUST_LAYER 2
#define CONFIG_LAYER 3
#define LAYER_COUNT 4

typedef const enum _EFFECTS {
  RANDOM_ON = 0,
#ifdef USE_WANDER
  WANDER,
#endif
  SPECTRUM_0,
  TIME_DOMAIN,
#ifdef USE_LINE_SPECTRUM
  SPECTRUM_LINE,
#endif
  CENTER_PULSE,
  NO_EFFECT,

#ifdef USE_SINGLE_FADE
  SINGLE_FADE,
#endif
  TWO_COLOR,
  DIFFUSION,
  WAVE0,
  EFFECT_COUNT
} EFFECTS;

typedef const enum _CONFIGS{
  FIRE0_CONFIG = 0,
  CENTER_WAVE_CONFIG,
  BOTTOM_BUBBLES_CONFIG,
  DIFFUSION_TIME_CONFIG,
  CONFIG_COUNT
} CONFIGURATIONS;

class Effects{
  public:
    Effects();
    void init();
    void run(EffectData &data);
    void push(IrInput input, uint8_t layer);
    void reset();
    void nextEffect(uint8_t layer);
    void prevEffect(uint8_t layer);
    void nextConfig();
    void prevConfig();

  private:
    unsigned long lastRun;
    unsigned long lastStep;
    void updateShouldStep(EffectData &data);

    Sign sign;

    void setEffect(uint8_t kEffect, uint8_t layer);
    void setConfig(uint8_t kConfig);
#ifdef DEBUG
    void printEffect(uint8_t kEffect);
#endif
    uint8_t cEffect[COLOR_LAYER+1];
    Effect* effect[COLOR_LAYER+1];
    uint8_t cConfig;

    Effect noEffect;
    RandomOn randomOn;
  #ifdef USE_SINGLE_FADE
    SingleFade singleFade;
  #endif
    TwoColor twoColor;
    Diffusion diffusion;
    Spectrum0 spectrum0;
    TimeDomain timeDomain;
  #ifdef USE_LINE_SPECTRUM
    SpectrumLine spectrumLine;
  #endif
    CenterPulse centerPulse;
  #ifdef USE_WANDER
    Wander wander;
  #endif
    Wave0 wave0;

    Adafruit_WS2801 strip;

    void updateStrip();
    void updateStrip(EffectData &data);
};
#endif

