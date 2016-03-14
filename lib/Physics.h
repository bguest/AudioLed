#ifndef PHYSICS_H
#define PHYSICS_H

#include "Arduino.h"
#include "Particle.h"

class Physics{
  public:
    virtual void apply(Particle particals[], uint8_t particleCount);
};


#endif
