#ifndef CENTER_SQUARE_H
#define CENTER_SQUARE_H

#define IS_USING_SOUND     0b001
#define IS_SQUARE_1        0b010
#define IS_CYCLE_LOOK_DIST 0b100
#define CENTER_SQUARE_SETTING_COUNT 0b1000
#define LOOK_DISTANCE_MAX 4

#include "Arduino.h"
#include "Effect.h"
//#include "Strobe.h"

class CenterSquare : public Effect {

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
    uint8_t lookDistanceCount;
    bool isOffCycle;
    unsigned long lastStep;
    void setCenter(Sign &sign, EffectData &data);
    void squareize(Sign &sign, uint8_t x, uint8_t y);
    void square0(Sign &sign, uint8_t x, uint8_t y);
    void square1(Sign &sign, uint8_t x, uint8_t y);
    bool updatePixel(Pixel *target, Pixel *source);

};

#endif

