#ifndef EMITTER_H
#define EMITTER_H

#include "PsConstants.h"

#include "Arduino.h"
#include "Particle.h"

class Emitter {
  public:
    virtual void emit(Particle &particle);
};

#endif
