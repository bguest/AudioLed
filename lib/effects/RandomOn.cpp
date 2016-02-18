#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> randomize();
}

void RandomOn::randomize(){
  onCount = random(LED_COUNT/);
  shouldReset = true;
  turnOn = true;
}

void RandomOn::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return; }

  if(shouldReset){
    sign.off();
  }
  for(uint8_t i = 0; i < onCount; i++){
    Pixel* pixel = sign.randomPixel();
    pixel->isOn = turnOn;
  }
}
