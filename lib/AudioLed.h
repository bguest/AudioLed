#ifndef AUDIO_LED_H
#define AUDIO_LED_H

#include "Effects.h"
#include "Sound.h"

class AudioLed{
  public:
    AudioLed();
    void init();
    void run();

  private:
    Effects effects;
    Sound sound;
    EffectData data;
};

#endif
