#ifndef EFFECTS_H
#define EFFECTS_H

#include "Adafruit_WS2801.h"

#define DATA_PIN 11
#define CLK_PIN 13

#define USE_LINE_SPECTRUM     1
#define USE_SINGLE_FADE       0
#define USE_WANDER            0
#define USE_PARTICLE_SYSTEM   0
#define USE_CENTER_SQUARE     1
#define USE_NEUMANN_AUTOMATA  0

typedef const enum _EFFECTS {
  RANDOM_ON = 0,
  STROBE,
#if USE_CENTER_SQUARE
  CENTER_SQUARE,
#endif
  BUBBLES,
#if USE_WANDER
  WANDER,
#endif
  SPECTRUM_0,
  TIME_DOMAIN,
#if USE_LINE_SPECTRUM
  SPECTRUM_LINE,
#endif
  CENTER_PULSE,
#if USE_NEUMANN_AUTOMATA
  NEUMANN_AUTOMATA,
#endif
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
  BUBBLES_0_CONFIG,
#if USE_CENTER_SQUARE
  SQUARE_0_CONFIG,
  SQUARE_1_CONFIG,
#endif
  STROBE_0_CONFIG,
  STROBE_1_CONFIG,
  STROBE_2_CONFIG,
  RANDOM_DIFFUSION_0_CONFIG,
  THREE_COLOR_RANDOM_0_CONFIG,
#if USE_NEUMANN_AUTOMATA
  NEUMANN_0_CONFIG,
#endif
#if USE_PARTICLE_SYSTEM
  PS_CENTER_FOUNTAIN,
  PS_FIRE0_CONFIG,
#endif
  CENTER_WAVE_CONFIG,
  BOTTOM_BUBBLES_CONFIG,
  CENTER_SPECTRUM_CONFIG,
  DIFFUSION_TIME_CONFIG,
  CONFIG_COUNT
} CONFIGURATIONS;


#define TEXT_LAYER 0
#define COLOR_LAYER 1
#define ADJUST_LAYER 2
#define CONFIG_LAYER 3
#define LAYER_COUNT 4

#include "effects/Effect.h"
#include "effects/Strobe.h"
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
#if USE_NEUMANN_AUTOMATA
  #include "effects/NeumannAutomata.h"
#endif
#if USE_CENTER_SQUARE
  #include "effects/CenterSquare.h"
#endif
#include "effects/Bubbles.h"


const uint8_t UPDATE_DURRATION = 5;

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
    void setEffects(uint8_t textLayer, uint8_t colorLayer);
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
  #if USE_NEUMANN_AUTOMA
    NeumannAutomata neumannAutomata;
  #endif
  #if USE_CENTER_SQUARE
    CenterSquare centerSquare;
  #endif
    Strobe strobe;
    Bubbles bubbles;

    Adafruit_WS2801 strip;

    void updateStrip();
    void updateStrip(EffectData &data);
};
#endif

