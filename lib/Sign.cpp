#include "Sign.h"

void Sign::init(){
  for(uint8_t i = 0; i< LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      Pixel* pixel = &pixels[i][j];
      pixel->x = i;
      pixel->y = j;
    }
  }

}

void Sign::off(){
  for(uint8_t i = 0; i<LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      Pixel *pixel = &pixels[i][j];
      pixel->brightness = 0;
      pixel->isOn = false;
    }
  }
}

Pixel* Sign::pixelAtIndex(uint8_t index){
  uint8_t x = ledXY[index][0];
  uint8_t y = ledXY[index][1];
  return &pixels[x][y];
}

Pixel* Sign::randomPixel(){
  uint8_t randX = random(LED_WIDTH);
  uint8_t randY = random(LED_HEIGHT);

  return &pixels[randX][randY];
}
