#include "Effects.h"
#include "effects/Effect.cpp"
#include "effects/RandomOn.cpp"
#include "effects/SingleFade.cpp"
#include "effects/TwoColor.cpp"
#include "effects/Diffusion.cpp"

Effects::Effects(){
  effect[0] = &randomOn;
  effect[1] = &diffusion;
  cEffect[0] = RANDOM_ON;
  cEffect[1] = DIFFUSION;
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip.begin();
  strip.show();
}

void Effects::run(){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    data.tempo = 3000;
    this->updateShouldStep();
    effect[0] -> run(sign, data);
    effect[1] -> run(sign, data);
    this -> updateStrip();
    strip.show();
  }
}

void Effects::updateShouldStep(){
  unsigned long currMillis = millis();
  if(currMillis - lastStep > data.tempo){
    data.shouldStep = true;
    lastStep = currMillis;
  }else{
    data.shouldStep = false;
  }
}

void Effects::setEffect(uint8_t kEffect, Layer layer){
  cEffect[layer] = kEffect;
  switch(kEffect){
    case RANDOM_ON: effect[layer] = &randomOn; break;
    case SINGLE_FADE: effect[layer] = &singleFade; break;
    case TWO_COLOR: effect[layer] = &twoColor; break;
    case DIFFUSION: effect[layer] = &diffusion; break;
  }
  effect[layer] -> randomize();
}

void Effects::changeEffect(){
  //cEffect++;
  //cEffect = cEffect % EFFECT_COUNT;
  //this -> setEffect(cEffect);
}

void Effects::updateStrip(){
  uint8_t offset = 0;
  for(uint8_t idx = offset; idx< LED_COUNT; idx++){
    Pixel* pixel = sign.pixelAtIndex(idx);
    strip.setPixelColor(idx-offset, pixel->color());
  }

}

