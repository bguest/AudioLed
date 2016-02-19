#include "Sign.h"

void Sign::init(){
  for(uint8_t i = 0; i< LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      Pixel* pixel = &pixels[LED_HEIGHT*i+j];
      pixel->x = i;
      pixel->y = j;
    }
  }

}

void Sign::off(){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    pixel->isOn = false;
  }
}

void Sign::black(){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    pixel->brightness = 0;
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
  return &pixels[LED_HEIGHT*x+y];
}

Pixel* Sign::randomPixel(){
  uint8_t rand = random(LED_WIDTH*LED_HEIGHT);
  return &pixels[rand];
}
