#ifndef SPECTRUM_LINE_H
#define SPECTRUM_LINE_H

#include "Arduino.h"

class SpectrumLine : public Effect{
  public:
    SpectrumLine();
    void randomize();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);

  private:
    uint8_t lineHeight;

};

#endif
