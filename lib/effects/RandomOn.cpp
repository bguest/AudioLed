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
    sign.randomPixel()->direction[0] = Up;
    sign.randomPixel()->direction[0] = Down;
  }
}

void RandomOn::push(IrInput input){
  Effect::push(input);
  switch(input){
    case DOWN: if(onCount > 0 ){ onCount--; } break;
    case UP: if(onCount < LED_COUNT*2){ onCount++; } break;
  }
}

void RandomOn::setConfig(uint8_t kConfig){
  switch(kConfig){

    case THREE_COLOR_RANDOM_0_CONFIG:
      onCount = random(1, 20);
      shouldReset = true;
      turnOn = true;
      break;

    case RANDOM_DIFFUSION_0_CONFIG:
      onCount = random(3,10);
      shouldReset = true;
      turnOn = true;
      break;

    default:
      break;

  }
}
