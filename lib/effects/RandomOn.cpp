#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> randomize();
}

void RandomOn::randomize(){
  onCount = random(10);
  shouldReset = true;
  turnOn = true;
}

void RandomOn::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return; }

  if(shouldReset){
    sign.off();
  }
  for(uint8_t i = 0; i < onCount; i++){
    uint8_t rand = random(0,LED_COUNT);
    Pixel* pixel = sign.pixelAtIndex(rand);
    pixel->isOn = turnOn;
  }
}
