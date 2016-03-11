#ifndef TIME_DOMAIN_H
#define TIME_DOMAIN_H

#include "Arduino.h"
#include "Effect.h"

class TimeDomain : public Effect {
  public:
    TimeDomain();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    unsigned long lastStep;
    uint16_t currVolume;
    uint8_t volume[LED_WIDTH];
    uint8_t band;

    void pushVolume(uint8_t volume);
};

#endif
