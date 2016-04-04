#ifndef DIFFUSION_H
#define DIFFUSION_H

#include "Arduino.h"
#include "Effect.h"

class Diffusion: public Effect{
  public:
    Diffusion();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void randomize();
    void setConfig(uint8_t kConfig);

  private:
    bool isFixedBoundary;
    uint16_t diffusionConstant;
    unsigned long lastStep;
    void diffuse(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT);
    uint8_t influence;

};
#endif
