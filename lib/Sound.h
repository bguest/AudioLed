#ifndef SOUND_H
#define SOUND_H

#include "EffectData.h"

class Sound {
  public:
    void init();
    void run(EffectData &data);

  private:
    uint16_t maxFreqAmp[7];

};
#endif
