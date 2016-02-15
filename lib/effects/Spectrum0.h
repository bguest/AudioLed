#ifndef SPECTRUM_0_H
#define SPECTRUM_0_H

#include "Arduino.h"

const int RESET_TIME = 5000;

class Spectrum0 : public Effect {

  public:
    Spectrum0();
    void run(Sign &sign, EffectData &data);

  private:
    uint16_t maxAmp[7];
    unsigned long lastMax[7];

};

#endif
