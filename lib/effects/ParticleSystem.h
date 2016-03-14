#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Arduino.h"
#include "Emitter.h"
#include "FireEmitter.h"
#include "FountainEmitter.h"
#include "Acceleration.h"

class ParticleSystem : public Effect {

  public:
    ParticleSystem();
    void run(Sign &sign, EffectData &data);
    void setConfig(uint8_t kConfig);
    void reset();

  private:
    Emitter* emitter;
    FountainEmitter fountainEmitter;
    FireEmitter fireEmitter;

    Physics* physics;
    Acceleration acceleration;

    Particle particles[MAX_PARTICLE_COUNT];
    uint8_t particleCount;
    void update();
    void render(Sign &sign);

    void addColor(Sign &sign, uint8_t row, uint8_t col, uint16_t hue, uint32_t value);

    uint8_t counter;
};


#endif
