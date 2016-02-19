#ifndef TEMPO_H
#define TEMPO_H

#include "Arduino.h"

const uint8_t TAP_COUNT = 8;

class Tempo{

  public:
    Tempo();
    void init();
    void tap();
    uint16_t tempo;
    bool isDoubleTap;

  private:
    const uint16_t MAXIMUM_PERIOD = 2500;
    const uint16_t DOUBLE_TAP_PERIOD = 200;

    uint8_t tapIdx;
    uint16_t tapTimes[TAP_COUNT];

    void runCalc();
};


#endif
