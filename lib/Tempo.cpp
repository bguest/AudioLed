#include "Tempo.h"

Tempo::Tempo(){
  tapIdx = 0;
  tempo = 1000;
}

void Tempo::init(){
  for(uint8_t idx = 0; idx < TAP_COUNT; idx++){
    tapTimes[idx] = 0;
  }
}

void Tempo::tap(){
  uint8_t idx = tapIdx % TAP_COUNT;

  tapTimes[idx] = millis();
  this -> runCalc();
  tapIdx++;
}

void Tempo::runCalc(){

  uint8_t beats = 0;
  uint16_t durration = 0;

  for(uint8_t idx = 1; idx < TAP_COUNT; idx++){
    int16_t diff = tapTimes[idx] - tapTimes[idx - 1];

    if(diff > DOUBLE_TAP_PERIOD && diff < MAXIMUM_PERIOD){
      beats++;
      durration += diff;
    }else if(diff > 0 && diff < DOUBLE_TAP_PERIOD){
      tapTimes[idx] = tapTimes[idx-1];
    }
  }
  if(beats > 0){
    tempo = durration/beats;
  }
}

