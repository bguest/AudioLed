#ifndef ACCELERATION_H
#define ACCELERATION_H

#include "Physics.h"

class Acceleration : public Physics{

  public:
    Acceleration();
    void apply(Particle particals[], uint8_t particleCount);
    uint8_t counter;

    uint8_t ax;
    uint8_t ay;
};
#endif
