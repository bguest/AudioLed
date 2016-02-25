#include "TwoColor.h"

TwoColor::TwoColor(){
  this -> randomize();
}

void TwoColor::randomize(){
  isTurnOffOff = true;
  hue[0] = random(0xFF);
  hue[1] = random(0xFF);
  hue[2] = random(0xFF);
}

void TwoColor::push(IrInput input){
  Effect::push(input);
  switch(input){
    case UP: hue[1]+= 2; break;
    case LEFT: hue[0]+= 2; break;
    case DOWN: hue[2]+= 2; break;
    case RIGHT: isTurnOffOff = !isTurnOffOff; break;
  }
}

void TwoColor::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return; }

  for(uint8_t i=0; i<LED_COUNT; i++){
    Pixel* pixel = sign.pixel(i);
    uint16_t h;
    switch(pixel->direction){
      case Up: h = hue[1]; break;
      case Off: h = hue[0]; break;
      case Down: h = hue[2]; break;
    }

    if(isTurnOffOff && pixel->direction == Off){
      pixel->value = 0;
    }else{
      pixel->hue[0] = h << 8;
      pixel->value = 0xFFFF;
    }
  }

}

