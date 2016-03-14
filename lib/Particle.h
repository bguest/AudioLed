#ifndef PARTICLE_H
#define PARTICLE_H

#include "Arduino.h"
#include "PsConstants.h"

#define IS_FIXED_MASK  0b1
#define IS_MASS_DECAY  0b10
#define IS_DIEING_MASK 0b100
#define IS_BOUNCE_MASK 0b1000

class Particle {
  public:
    uint8_t x;
    uint8_t y;
    int8_t vx;
    int8_t vy;
    uint8_t mass;
    uint8_t typeMask;

    uint8_t ttl; //time to live
    uint16_t hue; //hue

    void update();
};

#endif
