#include "Diffusion.h"

Diffusion::Diffusion(){
  this -> randomize();
}

void Diffusion::randomize(){
  lastStep = 0;
  diffusionConstant = 1000;
  influence = 0b1111;
}

void Diffusion::run(Sign &sign, EffectData &data){

  unsigned long currMillis = millis();
  unsigned long deltaT = currMillis - lastStep;
  lastStep = currMillis;

  sign.push();

  for(uint8_t i = 0; i<LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      Pixel* pixel = sign.pixel(i,j);
      if(pixel->direction == Up){
        pixel->hue[0] = 0xFFFF;
      }else{
        this->diffuse(sign, i, j, deltaT);
      }
      pixel->value = 0xFFFF;
    }
  }
}

void Diffusion::push(IrInput input){
  Effect::push(input);
  switch(input){
    case RIGHT: influence = ++influence % 16; break;
    case LEFT:
      if(influence == 0){
        influence = 0b1111;
      }else{
        influence--;
      }
      break;
    case CENTER: influence = 0b1111; break;
  }
}

void Diffusion::diffuse(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT){

  Pixel* pixel = sign.pixel(x,y);

  int32_t u[4];
  uint8_t idx = 0;
  if((influence & 0b0001) > 0){ u[idx++] = (x == 0 )           ? 0 : sign.pixel(x-1, y)->hue[1]; }
  if((influence & 0b0010) > 0){ u[idx++] = (x == LED_WIDTH-1)  ? 0 : sign.pixel(x+1, y)->hue[1]; }
  if((influence & 0b0100) > 0){ u[idx++] = (y == 0 )           ? 0 : sign.pixel(x, y-1)->hue[1]; }
  if((influence & 0b1000) > 0){ u[idx++] = (y == LED_HEIGHT-1) ? 0 : sign.pixel(x, y+1)->hue[1]; }

  int32_t v = diffusionConstant;

  int32_t h0 = pixel->hue[1];
  int32_t h = 0;

  for(uint8_t i=0; i<idx; i++){
    h += u[i] - h0;
  }
  h = h*deltaT/v + h0; //*(1-deltaT/v);

  if(h < 0){ h = 0; }
  else if(h > 0xFFFF){ h = 0xFFFF; }
  pixel->hue[0] = h;
}
