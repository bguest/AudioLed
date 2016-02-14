#ifndef AUDIO_LED_H
#define AUDIO_LED_H

#include "Effects.h"

class AudioLed{
  public:
    AudioLed();
    void init();
    void run();

  private:
    Effects effects;
};

#endif
