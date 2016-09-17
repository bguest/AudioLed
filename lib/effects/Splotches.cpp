#include "Splotches.h"

Splotches::Splotches(){

}

void Bubbles::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();
  if( data.volume > mVolume ){ mVolume = data.volume;}
  if( currMillis - lastStep < data.tempo/perTempo ) { return; }
  lastStep = currMillis;
  data.shouldStep = true;

  if(sign.count(Down, 0) == 0){
    sign.setDirection(Down);
    for(uint8_t i=0; i<3; i++){
      Pixel* pixel = sign.randomPixel()
      pixel->direction[0] = Up;
      pixel->hue[0] = random(0xFFFF);
    }
  }else{
    sign.push();
    for(uint8_t i=0; i<LED_WIDTH; i++){
      for(uint8_t j=0; j<LED_HEIGHT; j++){
        this->splotches(sign, i, j);
      }
    }
  }

}

void Splotches::splotches(Sign &sign, uint8_t x, uint8_t y){
  Pixel *pixel = sign.pixel(x,y);
  Direction currDirection = pixel->direction[1];

  // Initialize count
  uint8_t count[3]; for(uint8_t i = 0; i<3; i++){ count[i] = 0; }

  /*
  for(int8_t i = -1; i<=1; i++){
    for(int8_t j = -1; j<=1; j++){
      if(i != 0 && j != 0){
        Direction dir = sign.pixel(x+i,x+j)->direction[1];
        count[dir]++;
      }
    }
  }
  */
  Direction dir;

  dir = sign.pixel(x+1,y)->direction[1]; count[dir]++;
  dir = sign.pixel(x-1,y)->direction[1]; count[dir]++;
  dir = sign.pixel(x,y+1)->direction[1]; count[dir]++;
  dir = sign.pixel(x,y-1)->direction[1]; count[dir]++;

  switch(currDirection){
    case Off: break;
    case Up:
              if(count[Down] != 0){
                pixel->direction[0] = Off;
              }
              break;
    case Down:
              if(count[Up] > 0){
                pixel->direction[0] = Up;
              }
              break;
  }

}

