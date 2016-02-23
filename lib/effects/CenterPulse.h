#ifndef CENTER_PULSE_H
#define CENTER_PULSE_H

#include "Arduino.h"

class CenterPulse : public Effect {
  public:
    CenterPulse();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);

  private:
    uint8_t smoothing;
    uint16_t maxVal;

};

#endif
