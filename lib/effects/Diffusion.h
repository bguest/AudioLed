#ifndef DIFFUSION_H
#define DIFFUSION_H

#include "Arduino.h"

class Diffusion : public Effect{
  public:
    Diffusion();
    void run(Sign &sign, EffectData &data);
    void randomize();

  private:
    uint16_t diffusionConstant;
    unsigned long lastStep;
    void diffuse(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT);

};
#endif
