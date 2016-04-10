#ifndef STROBE_H
#define STROBE_H

#include "Arduino.h"
#include "Effect.h"

class Strobe: public Effect {

  public:
    Strobe();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    uint8_t perTempo;
    unsigned long lastStep;

};

#endif
