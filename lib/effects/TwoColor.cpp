#include "TwoColor.h"
#define HUE_STEP 0x0100
#define STEP_SIZE 4
#define FADE_STEP 2
#define FADE_MAX 100

TwoColor::TwoColor(){
  this -> randomize();
}

void TwoColor::randomize(){

  for(uint8_t i=0; i<3; i++){
    value[i] = 0xFF;
    saturation[i] = 0xFF;
    hue[i] = random(0xFF);
    fadeSpeed[i] = random(-FADE_MAX, FADE_MAX);
  }
}

void TwoColor::push(IrInput input){
  switch(input){
    case CENTER: pushDirection = (++pushDirection % 3); break;
    case UP: value[pushDirection] += STEP_SIZE; break;
    case LEFT: hue[pushDirection] += HUE_STEP; break;
    case DOWN: saturation[pushDirection] += STEP_SIZE; break;
    case RIGHT:
               if(++fadeSpeed[pushDirection] > FADE_MAX){
                 fadeSpeed[pushDirection] = 0;
               }
               break;
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

  switch(kConfig){
    case STROBE_0_CONFIG:
      for(uint8_t i=0; i<3; i++){ saturation[i] = 0; }
      value[Up] = 0xFF;
      value[Off] = 0x0;
      value[Down] = 0x0;
      break;

    case STROBE_1_CONFIG:
    case SQUARE_0_CONFIG:
      hue[Up] = 0xA500;
      hue[Off] = 0x0000;
      hue[Down] = 0x3000;
      break;

    case FIRE0_CONFIG:
      value[Off] = 0x0;
      hue[Up] = 0x0F00;
      hue[Down] = 0x0100;
      break;

    case THREE_COLOR_RANDOM_0_CONFIG:
      hue[Up] = 0x0000;
      hue[Down] = 0x0000;
      hue[Off] = 0x0000;
      fadeSpeed[Up] = -80;
      fadeSpeed[Down] = 60;
      fadeSpeed[Off] = 10;
      break;

    case NEUMANN_0_CONFIG:
      hue[Up] = 0xA500;
      hue[Down] = 0x3000;
      fadeSpeed[Up] = 30;
      fadeSpeed[Off] = 60;
      fadeSpeed[Down] = -50;
      break;
  }
}

void TwoColor::run(Sign &sign, EffectData &data){

  for(uint8_t idx = 0; idx < 3; idx++){
    hue[idx] += fadeSpeed[idx];
  }

  for(uint8_t i=0; i<LED_COUNT; i++){

    Pixel* pixel = sign.pixel(i);
    uint8_t idx = pixel->direction[0];

    pixel->hue[0] = hue[idx];
    pixel->value = value[idx];
    pixel->saturation = saturation[idx];

  }

}

