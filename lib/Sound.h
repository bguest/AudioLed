#ifndef SOUND_H
#define SOUND_H

#include "EffectData.h"

class Sound {
  public:
    void init();
    void run(EffectData &data);

  private:
    unsigned long lastCollect;
    uint16_t volume;
    uint16_t freqAmp[7];

};
#endif
