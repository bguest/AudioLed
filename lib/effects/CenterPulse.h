#ifndef CENTER_PULSE_H
#define CENTER_PULSE_H

#include "Arduino.h"

class CenterPulse : public Effect {
  public:
    CenterPulse();
    void randomize();
    void run(Sign &sign, EffectData &data);

};

#endif
