#ifndef SPECTRUM_0_H
#define SPECTRUM_0_H

#include "Arduino.h"
#include "Effect.h"

const int RESET_TIME = 5000;

class Spectrum0 : public Effect {

  public:
    Spectrum0();
    void run(Sign &sign, EffectData &data);

  private:
    uint16_t maxAmp[FREQ_COUNT];
    bool isHighOn;
    unsigned long lastMax[FREQ_COUNT];

};

#endif
