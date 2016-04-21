#include "Sign.h"

void Sign::init(){
  for(uint8_t i = 0; i< LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      Pixel* pixel = &pixels[LED_HEIGHT*i+j];
      //pixel->x = i;
      //pixel->y = j;
    }
  }

}

void Sign::off(){
  this->setDirection(Off);
}

void Sign::setDirection(Direction direction){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    for(uint8_t j = 0; j<2; j++){
      pixel->direction[j] = direction;
    }
  }
}

uint8_t Sign::count(Direction direction, uint8_t layer){
  uint8_t count = 0;
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    if(pixel->direction[layer] == direction){
      count++;
    }
  }
  return count;
}

void Sign::black(){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    pixel->value = 0;
  }
}

void Sign::push(){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    pixel->push();
  }
}

Pixel* Sign::pixel(uint8_t index){
  uint8_t x = ledXY[index][0];
  uint8_t y = ledXY[index][1];
  return &pixels[LED_HEIGHT*x+y];
}

Pixel* Sign::pixel(uint8_t x, uint8_t y){
  if(x > LED_WIDTH && x < 128){ x = LED_WIDTH-1; }
  else if( x > LED_WIDTH){ x = 0; }

  if(y > LED_HEIGHT && y < 128){ y = LED_HEIGHT-1; }
  else if( y > LED_HEIGHT){ y = 0; }

  return &pixels[LED_HEIGHT*x+y];
}

Pixel* Sign::randomPixel(){
  uint8_t rand = random(LED_WIDTH*LED_HEIGHT);
  return &pixels[rand];
}
