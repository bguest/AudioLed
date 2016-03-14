#ifndef FOUNTAIN_EMITTER_H
#define FOUNTAIN_EMITTER_H

#include "Arduino.h"
#include "Emitter.h"
#include "Particle.h"

class FountainEmitter : public Emitter{
  public:
    static byte minLife;
    static byte maxLife;
    signed char vx;  //horizontal velocity for emitted particles
    signed char vy;  //vertical velocity for emitted particles
    byte var; //emitted particles velocity variance
    Particle source; //source point
    uint16_t currHue;

    FountainEmitter();
    void emit(Particle &particle);
private:
    byte _hVar;
};
#endif
