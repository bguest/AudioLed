#ifndef CENTER_SQUARE_H
#define CENTER_SQUARE_H

#define IS_USING_SOUND 0b01
#define IS_SQUARE_1    0b10
#define CENTER_SQUARE_SETTING_COUNT 0b100
#define LOOK_DISTANCE_MAX 2

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
    uint8_t settingsMask;
    uint8_t lookDistance;
    unsigned long lastStep;
    void setCenter(Sign &sign, EffectData &data);
    void squareize(Sign &sign, uint8_t x, uint8_t y);
    void square0(Sign &sign, uint8_t x, uint8_t y);
    void square1(Sign &sign, uint8_t x, uint8_t y);
    bool updatePixel(Pixel *target, Pixel *source);

};

#endif

