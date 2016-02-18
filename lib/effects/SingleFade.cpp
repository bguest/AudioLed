#include "SingleFade.h"

SingleFade::SingleFade(){
  this -> randomize();
}

void SingleFade::randomize(){
  lastStep = 0;
  activePixel[0] = 0;
  activePixel[1] = 1;
  maxHueStep = random(0x0FFF);
}

void SingleFade::run(Sign &sign, EffectData &data){

  unsigned long currMillis = millis();
  if(currMillis - lastStep > data.tempo){
    lastStep = currMillis;
    this ->updateActive();
  }
  sign.off();

  for(uint8_t i=0; i<2; i++){
    Pixel* pixel = sign.pixel(activePixel[i]);
    pixel->hue += data.volume << 2;

    if(data.shouldStep){
      pixel->hue += random(maxHueStep);
    }

    uint8_t brightness;
    if(i == 0){
       brightness = 255*(currMillis - lastStep)/data.tempo;
    }else{
       brightness = 255 - 255*(currMillis - lastStep)/data.tempo;
    }
    pixel->brightness = brightness << 8;
  }
}

void SingleFade::updateActive(){
  activePixel[1] = activePixel[0];
  uint8_t sample[LED_COUNT-1];
  uint8_t i = 0;
  for(uint8_t j=0; j<4; j++){
    if(j != activePixel[1]){
      sample[i] = j;
      i++;
    }
  }
  activePixel[0] = sample[random(LED_COUNT-1)];
}
