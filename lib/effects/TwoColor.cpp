#include "TwoColor.h"
#define HUE_STEP 0x0100
#define FADE_STEP 1
#define FADE_MAX 80
#define IS_FADE_MASK 0b01

TwoColor::TwoColor(){
  this -> randomize();
}

void TwoColor::randomize(){
  settingMask = random(0,0b11);
  for(uint8_t i=0; i<3; i++){
    value[i] = 0xFF;
    saturation[i] = 0xFF;
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

  // Defaults
  for(uint8_t i=0; i<3; i++){
    value[i] = 0xFF;
    saturation[i] = 0xFF;
    hue[i] = 0x0100;
    fadeSpeed[i] = 0;
  }
  settingMask = 0;

  switch(kConfig){
    case STROBE_0_CONFIG:
      for(uint8_t i=0; i<3; i++){ saturation[i] = 0; }
      value[Up] = 0xFF;
      value[Off] = 0x0;
      value[Down] = 0x0;
      break;

    case FIRE0_CONFIG:
      value[Off] = 0x0;
      hue[Up] = 0x0F00;
      hue[Down] = 0x0100;
      break;

    case THREE_COLOR_RANDOM_0_CONFIG:
      settingMask = IS_FADE_MASK;
      hue[Up] = 0x0000;
      hue[Down] = 0x0000;
      hue[Off] = 0x0000;
      fadeSpeed[Up] = -80;
      fadeSpeed[Down] = 60;
      fadeSpeed[Off] = 10;
      break;

    case NEUMANN_0_CONFIG:
      settingMask = IS_FADE_MASK;
      hue[Up] = 0xA500;
      hue[Down] = 0x3000;
      fadeSpeed[Up] = 30;
      fadeSpeed[Off] = 60;
      fadeSpeed[Down] = -50;
      break;
  }
}

void TwoColor::run(Sign &sign, EffectData &data){
  if( !data.shouldStep && (settingMask & IS_FADE_MASK) == 0  ){ return; }

  if( (settingMask & IS_FADE_MASK) > 0){
    for(uint8_t idx = 0; idx < 3; idx++){
      hue[idx] += fadeSpeed[idx];
    }
  }

  for(uint8_t i=0; i<LED_COUNT; i++){

    Pixel* pixel = sign.pixel(i);
    uint8_t idx = pixel->direction[0];

    pixel->hue[0] = hue[idx];
    pixel->value = value[idx];
    pixel->saturation = saturation[idx];

  }

}

