#ifndef SPECTRUM_0_H
#define SPECTRUM_0_H

#include "Arduino.h"
#include "Effect.h"

class Spectrum0 : public Effect {

  public:
    Spectrum0();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    uint16_t maxAmp[FREQ_COUNT];
    bool isHighOn;
    unsigned long lastMax[FREQ_COUNT];
    uint8_t rolloff;

};

#endif
