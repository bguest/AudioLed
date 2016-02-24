#include "TwoColor.h"

TwoColor::TwoColor(){
  this -> randomize();
}

void TwoColor::randomize(){
  hue[0] = random(0xFF);
  hue[1] = random(0xFF);
}

void TwoColor::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return; }

  for(uint8_t i=0; i<LED_COUNT; i++){
    Pixel* pixel = sign.pixel(i);
    uint16_t h = pixel->direction == Up ? hue[0] : hue[1];
    pixel->hue[0] = h << 8;
    pixel->value = 0xFFFF;
  }

}

