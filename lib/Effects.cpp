#include "Effects.h"
#include "effects/Effect.cpp"
#include "effects/Diffusion.cpp"
#include "effects/RandomOn.cpp"
#include "effects/SingleFade.cpp"
#include "effects/TwoColor.cpp"
#include "effects/Spectrum0.cpp"
#include "effects/Wander.cpp"

Effects::Effects(){
  effect[0] = &spectrum0;
  cEffect[0] = SPECTRUM_0;
  effect[1] = &diffusion;
  cEffect[1] = DIFFUSION;
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip.begin();
  strip.show();
}

void Effects::run(EffectData &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    data.tempo = 2000;
    this->updateShouldStep(data);
    effect[0] -> run(sign, data);
    effect[1] -> run(sign, data);
    this -> updateStrip();
    strip.show();
  }
}

void Effects::updateShouldStep(EffectData &data){
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
    case SPECTRUM_0: effect[layer] = &spectrum0; break;
    case WANDER: effect[layer] = &wander; break;
  }
  effect[layer] -> randomize();
}

void Effects::nextEffect(Layer layer){
  cEffect[layer]++;
  cEffect[layer] = cEffect[layer] % EFFECT_COUNT;
  this -> setEffect(cEffect[layer], layer);
}

void Effects::prevEffect(Layer layer){
  if(cEffect[layer] == 0){
    cEffect[layer] = EFFECT_COUNT - 1;
  }else{
    cEffect[layer]--;
    cEffect[layer] = cEffect[layer] % EFFECT_COUNT;
  }
  this -> setEffect(cEffect[layer], layer);
}

void Effects::updateStrip(){
  uint8_t offset = 0;
  for(uint8_t idx = offset; idx< LED_COUNT; idx++){
    Pixel* pixel = sign.pixel(idx);
    strip.setPixelColor(idx-offset, pixel->color());
  }

}

