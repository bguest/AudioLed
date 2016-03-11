#ifndef TWO_COLOR_H
#define TWO_COLOR_H

#include "Arduino.h"
#include "Effect.h"

class TwoColor : public Effect{

  public:
    TwoColor();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void randomize();
    void setConfig(uint8_t kConfig);

  private:
    uint16_t hue[3];
    int8_t fadeSpeed[3];
    uint8_t settingMask;
};
#endif
