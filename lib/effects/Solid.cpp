#include "Solid.h"

Solid::Solid(){
  direction = Off;
}

void Solid::run(Sign &sign, EffectData &data){

  for(uint8_t i=0; i<LED_COUNT; i++){
    sign.pixel(i) -> direction[0] = direction;
  }

}

void Solid::push(IrInput input){
  Effect::push(input);
  switch(input){
    case UP:   direction = Up; break;
    case RIGHT: direction = Off; break;
    case DOWN: direction = Down; break;
  }
}

void Solid::setConfig(uint8_t kConfig){
  switch(kConfig){
    case SOLID_FADE_CONFIG: direction = Off; break;
  }
}
