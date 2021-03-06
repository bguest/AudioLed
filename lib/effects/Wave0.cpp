#include "Wave0.h"

Wave0::Wave0(){
  this->randomize();
  influence = 0b1111;
}

void Wave0::randomize(){
  forceConstant = random(20, 50);
  velocityConstant = random(0xF000, 0x20000);
  isFixedBoundary = random(0, 1);
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

void Wave0::push(IrInput input){
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
    case UP:
      if( forceConstant < 0xFFF ) {
        ++forceConstant;
      }else{
        forceConstant = 0;
      };
      break;
    case DOWN:
      isFixedBoundary = !isFixedBoundary;
      break;
    case CENTER:
      influence = 0b1111;
      break;
  }

}
void Wave0::setConfig(uint8_t kConfig){
  switch(kConfig){

    case CENTER_WAVE_CONFIG:
      influence = 0b1111;
      isFixedBoundary = false;
      velocityConstant = 0x10000;
      break;

    case CENTER_SPECTRUM_CONFIG:
      influence = 0b1100;
      isFixedBoundary = false;
      velocityConstant = 0xF000;
      break;

    case BOTTOM_BUBBLES_CONFIG:
      influence = 0b0111;
      isFixedBoundary = false;
      velocityConstant = 0x10000;
      break;
  }
}

void Wave0::wave(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT2){

  Pixel* pixel = sign.pixel(x,y);

  int32_t u[4];
  uint8_t idx = 0;
  uint16_t boundary = isFixedBoundary ? (0xFFFF>1) : pixel->hue[0];
  if((influence & 0b0001) > 0){ u[idx++] = (x == 0 )           ? boundary : sign.pixel(x-1, y)->hue[1]; }
  if((influence & 0b0010) > 0){ u[idx++] = (x == LED_WIDTH-1)  ? boundary : sign.pixel(x+1, y)->hue[1]; }
  if((influence & 0b0100) > 0){ u[idx++] = (y == 0 )           ? boundary : sign.pixel(x, y-1)->hue[1]; }
  if((influence & 0b1000) > 0){ u[idx++] = (y == LED_HEIGHT-1) ? boundary : sign.pixel(x, y+1)->hue[1]; }

  int32_t c = velocityConstant;

  int32_t h0 = pixel->hue[1];
  int32_t h1 = pixel->hue[2];
  int32_t h = 0;

  for(uint8_t i=0; i<idx; i++){
    h += u[i] - h0;
  }
  int32_t f = 0;
  if( pixel->direction[0] == Up ){ f = forceConstant; }
  else if( pixel-> direction[0] == Down){ f = -forceConstant; }
  h = 2*h0 - h1 + h*deltaT2/c + f;

  if(h < 0){ h = 0; }
  else if(h > 0xFFFF){ h = 0xFFFF; }
  pixel->hue[0] = h;
  pixel->value = 0xFF;
}

