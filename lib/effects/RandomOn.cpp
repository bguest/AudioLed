#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> randomize();
}

void RandomOn::randomize(){
  onCount = random(LED_COUNT/2);
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
    pixel->direction = Up;
    sign.randomPixel()->direction = Down;
  }
}

void RandomOn::push(IrInput input){
  Effect::push(input);
  switch(input){
    case DOWN: if(onCount > 0 ){ onCount--; } break;
    case UP: if(onCount < LED_COUNT*2){ onCount++; } break;
  }
}
