#ifndef FIRE_EMITTER_H
#define FIRE_EMITTER_H

#include "Arduino.h"
#include "Emitter.h"
#include "Particle.h"

class FireEmitter : public Emitter {
  public:
    static uint8_t baseHue;
    static uint8_t maxTtl;
    unsigned int counter;
    boolean cycleHue;

    FireEmitter();
    void emit(Particle &particle);
};


#endif
