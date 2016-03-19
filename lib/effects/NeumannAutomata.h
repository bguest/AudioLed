#ifndef NEUMANN_AUTOMATA_H
#define NEUMANN_AUTOMATA_H

#include "Arduino.h"

class NeumannAutomata : public Effect{

  public:
    NeumannAutomata();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    uint8_t kRule;
    uint8_t neighborhoodState(Sign &sign, uint8_t x, uint8_t y);
    void setPixel(Pixel *pixel, uint8_t state);

};

#endif
