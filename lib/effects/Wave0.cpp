#include "Wave0.h"

Wave0::Wave0(){
  this->randomize();
}

void Wave0::randomize(){
  forceConstant = random(20, 50);
  velocityConstant = random(0xF000, 0x20000); 
  unsigned long currMillis = millis();
  time[0] = currMillis;
  time[1] = currMillis + 5;
}

void Wave0::run(Sign &sign, EffectData &data){

  unsigned long currMillis = millis();
  unsigned long deltaT2 = (currMillis - time[0])*(time[0] - time[1]);
  time[1] = time[0];
  time[0] = currMillis;

  sign.push();

  for(uint8_t i = 0; i<LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      this -> wave(sign, i, j, deltaT2);
    }
  }

}
void Wave0::wave(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT2){

  Pixel* pixel = sign.pixel(x,y);

  int32_t u[4];
  u[0] = (x == 0 )          ? 0xFFFF >> 1 : sign.pixel(x-1, y)->hue[1];
  u[1] = (x == LED_WIDTH)   ? 0xFFFF >> 1 : sign.pixel(x+1, y)->hue[1];
  u[2] = (y == 0 )          ? 0xFFFF >> 1 : sign.pixel(x, y-1)->hue[1];
  u[3] = (y == LED_HEIGHT ) ? 0xFFFF >> 1 : sign.pixel(x, y+1)->hue[1];

  int32_t c = velocityConstant;

  int32_t h0 = pixel->hue[1];
  int32_t h1 = pixel->hue[2];
  int32_t h = 0;

  for(uint8_t i=0; i<4; i++){
    h += u[i] - h0;
  }
  int32_t f = pixel->isOn ? forceConstant : 0;
  h = 2*h0 - h1 + h*deltaT2/c + f;

  if(h < 0){ h = 0; }
  else if(h > 0xFFFF){ h = 0xFFFF; }
  pixel->hue[0] = h;
  pixel->brightness = 0xFFFF;
}

