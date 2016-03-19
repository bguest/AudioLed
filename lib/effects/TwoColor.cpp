#include "TwoColor.h"
#define HUE_STEP 0x0100
#define FADE_STEP 1
#define FADE_MAX 30
#define IS_OFF_MASK 0b10
#define IS_FADE_MASK 0b01

TwoColor::TwoColor(){
  this -> randomize();
}

void TwoColor::randomize(){
  settingMask = random(0,0b11);
  for(uint8_t i=0; i<3; i++){
    hue[i] = random(0xFF);
    fadeSpeed[i] = random(-FADE_MAX, FADE_MAX);
  }
}

void TwoColor::push(IrInput input){
  Effect::push(input);
  int8_t idx = -1;
  switch(input){
    case UP:   idx = Up; break;
    case LEFT: idx = Off; break;
    case DOWN: idx = Down; break;
    case RIGHT:
               settingMask++;
               if(settingMask > 0b11){settingMask = 0;}
               break;
  }

  if(idx < 0 ){return;}

  if( (settingMask & IS_FADE_MASK) > 0){
    fadeSpeed[idx]+= FADE_STEP;
    if(fadeSpeed[idx] > FADE_MAX){
      fadeSpeed[idx] = -FADE_MAX;
    }
  }else{
    hue[idx] += HUE_STEP;
  }

}
void TwoColor::setConfig(uint8_t kConfig){
  switch(kConfig){
    case FIRE0_CONFIG:
      settingMask = IS_OFF_MASK;
      hue[Up] = 0x0F00;
      hue[Down] = 0x0100;
      break;

    case NEUMANN_0_CONFIG:
      settingMask = IS_FADE_MASK;
      hue[Up] = 0xA500;
      hue[Down] = 0x3000;
      fadeSpeed[Up] = 30;
      fadeSpeed[Off] = 50;
      fadeSpeed[Down] = -20;
      break;
  }
}

void TwoColor::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return; }

  if( (settingMask & IS_FADE_MASK) > 0){
    for(uint8_t idx = 0; idx < 3; idx++){
      hue[idx]+=fadeSpeed[idx];
    }
  }

  for(uint8_t i=0; i<LED_COUNT; i++){

    Pixel* pixel = sign.pixel(i);
    uint8_t idx = pixel->direction[0];

    if( (settingMask & IS_OFF_MASK) > 0 && pixel->direction[0] == Off ){
      pixel->value = 0;
    }else{
      pixel->hue[0] = hue[idx];
      pixel->value = 0xFFFF;
    }

  }

}

