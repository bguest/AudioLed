#ifndef EFFECTS_H
#define EFFECTS_H

#define DATA_PIN 11
#define CLK_PIN 13

#define USE_LINE_SPECTRUM     1
#define USE_SINGLE_FADE       0
#define USE_WANDER            0
#define USE_PARTICLE_SYSTEM   0

#include "effects/Effect.h"
#include "effects/Diffusion.h"
#include "effects/RandomOn.h"
#include "effects/TwoColor.h"
#if USE_SINGLE_FADE
  #include "effects/SingleFade.h"
#endif
#include "effects/Spectrum0.h"
#if USE_WANDER
  #include "effects/Wander.h"
#endif
#include "effects/Wave0.h"
#if USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.h"
#endif
#include "effects/CenterPulse.h"
#include "effects/TimeDomain.h"
#if USE_PARTICLE_SYSTEM
  #include "effects/ParticleSystem.h"
#endif
#include "effects/NeumannAutomata.h"
#include "effects/Strobe.h"
#include "effects/CenterSquare.h"

#include "Adafruit_WS2801.h"

const uint8_t UPDATE_DURRATION = 5;

#define TEXT_LAYER 0
#define COLOR_LAYER 1
#define ADJUST_LAYER 2
#define CONFIG_LAYER 3
#define LAYER_COUNT 4

typedef const enum _EFFECTS {
  RANDOM_ON = 0,
  STROBE,
  CENTER_SQUARE,
#if USE_WANDER
  WANDER,
#endif
  SPECTRUM_0,
  TIME_DOMAIN,
#if USE_LINE_SPECTRUM
  SPECTRUM_LINE,
#endif
  CENTER_PULSE,
  NEUMANN_AUTOMATA,
  NO_EFFECT,

#if USE_SINGLE_FADE
  SINGLE_FADE,
#endif
  TWO_COLOR,
  DIFFUSION,
  WAVE0,
#if USE_PARTICLE_SYSTEM
  PARTICLE_SYSTEM,
#endif
  EFFECT_COUNT
} EFFECTS;

typedef const enum _CONFIGS{
  FIRE0_CONFIG = 0,
  SQUARE_0_CONFIG,
  STROBE_0_CONFIG,
  FADE_SQUARE_0_CONFIG,
  STROBE_1_CONFIG,
  RANDOM_DIFFUSION_0_CONFIG,
  THREE_COLOR_RANDOM_0_CONFIG,
  NEUMANN_0_CONFIG,
#if USE_PARTICLE_SYSTEM
  PS_CENTER_FOUNTAIN,
  PS_FIRE0_CONFIG,
#endif
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
  #if USE_SINGLE_FADE
    SingleFade singleFade;
  #endif
    TwoColor twoColor;
    Diffusion diffusion;
    Spectrum0 spectrum0;
    TimeDomain timeDomain;
  #if USE_LINE_SPECTRUM
    SpectrumLine spectrumLine;
  #endif
    CenterPulse centerPulse;
  #if USE_WANDER
    Wander wander;
  #endif
    Wave0 wave0;
  #if USE_PARTICLE_SYSTEM
    ParticleSystem particleSystem;
  #endif
    NeumannAutomata neumannAutomata;
    Strobe strobe;
    CenterSquare centerSquare;

    Adafruit_WS2801 strip;

    void updateStrip();
    void updateStrip(EffectData &data);
};
#endif

