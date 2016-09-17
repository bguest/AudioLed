#ifndef SPLOTCHES_H
#define SPLOTCHES_H

#include "Arduino.h"
#include "Effect.h"

class Splotches : public Effect {
  public:
    Splotches();
    void run(Sign &sign, EffectData &data);
    //void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    unsigned long lastStep;
    uint8_t perTempo;
    void splotches(Sign &sign, uint8_t x, uint8_t y);

#endif
