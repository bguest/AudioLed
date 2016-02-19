#include "Diffusion.h"

Diffusion::Diffusion(){
  this -> randomize();
}

void Diffusion::randomize(){
  lastStep = 0;
  diffusionConstant = 1000;
}

void Diffusion::run(Sign &sign, EffectData &data){

  unsigned long currMillis = millis();
  unsigned long deltaT = currMillis - lastStep;
  lastStep = currMillis;

  sign.push();

  for(uint8_t i = 0; i<LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      Pixel* pixel = sign.pixel(i,j);
      if(pixel->isOn){
        pixel->hue[1] = 0xFFFF;
      }else{
        this->diffuse(sign, i, j, deltaT);
      }
      pixel->brightness = 0xFFFF;
    }
  }
}

void Diffusion::diffuse(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT){

  Pixel* pixel = sign.pixel(x,y);

  int32_t u[4];
  u[0] = (x == 0 )          ? 0 : sign.pixel(x-1, y)->hue[1];
  u[1] = (x == LED_WIDTH)   ? 0 : sign.pixel(x+1, y)->hue[1];
  u[2] = (y == 0 )          ? 0 : sign.pixel(x, y-1)->hue[1];
  u[3] = (y == LED_HEIGHT ) ? 0 : sign.pixel(x, y+1)->hue[1];

  int32_t v = diffusionConstant;

  int32_t h0 = pixel->hue[1];
  int32_t h = 0;

  for(uint8_t i=0; i<4; i++){
    h += u[i] - h0;
  }
  h = h*deltaT/v + h0; //*(1-deltaT/v);

  if(h < 0){ h = 0; }
  else if(h > 0xFFFF){ h = 0xFFFF; }
  pixel->hue[0] = h;
}
