#ifndef AUDIO_LED_H
#define AUDIO_LED_H

#include "Sound.h"
#include "Effects.h"
#include "Tempo.h"
#include "EffectData.h"
#include "Remote.h"

class AudioLed{
  public:
    AudioLed();
    void init();
    void run();

  private:
    Effects effects;
    Sound sound;
    Tempo tempo;
    Remote remote;
    EffectData data;
    uint8_t pushLayer;
    void handleRemote();
};

#endif
