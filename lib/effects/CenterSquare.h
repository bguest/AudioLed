#ifndef CENTER_SQUARE_H
#define CENTER_SQUARE_H

#include "Arduino.h"
#include "Effect.h"

class CenterSquare: public Effect {

  public:
    CenterSquare();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    uint8_t perTempo;
    uint16_t mVolume;
    unsigned long lastStep;
    void setCenter(Sign &sign, EffectData &data);
    void squareize(Sign &sign, uint8_t x, uint8_t y);
    bool updatePixel(Pixel *target, Pixel *source);

};

#endif

