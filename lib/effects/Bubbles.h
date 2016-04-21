#ifndef BUBBLES_H
#define BUBBLES_H

#include "Arduino.h"
#include "Effect.h"

class Bubbles : public Effect {
  public:
    Bubbles();
    void run(Sign &sign, EffectData &data);
    //void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    uint16_t mVolume;
    unsigned long lastStep;
    uint8_t perTempo;
    bool shouldReset;
    void bubble(Sign &sign, uint8_t x, uint8_t y);

};


#endif
