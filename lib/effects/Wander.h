#ifndef WANDER_H
#define WANDER_H

#include "Arduino.h"
#include "Effect.h"

class Wander : public Effect{

  public:
    Wander();
    void run(Sign &sign, EffectData &data);

  private:
    bool keepOn;
    uint8_t x;
    uint8_t y;
    bool valid(uint8_t x, uint8_t y, Sign &sign);
    void get(uint8_t direction, uint8_t &x, uint8_t &y);
    bool canMove(Sign &sign);

};

#endif
