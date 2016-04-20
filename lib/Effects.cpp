#include "Effects.h"

#include "effects/Effect.cpp"
#include "effects/Diffusion.cpp"
#include "effects/RandomOn.cpp"
#if USE_SINGLE_FADE
  #include "effects/SingleFade.cpp"
#endif
#include "effects/TwoColor.cpp"
#include "effects/Spectrum0.cpp"
#if USE_WANDER
  #include "effects/Wander.cpp"
#endif
#include "effects/Wave0.cpp"
#if USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.cpp"
#endif
#include "effects/CenterPulse.cpp"
#include "effects/TimeDomain.cpp"
#if USE_PARTICLE_SYSTEM
  #include "effects/ParticleSystem.cpp"
#endif
#include "effects/NeumannAutomata.cpp"
#if USE_CENTER_SQUARE
  #include "effects/CenterSquare.cpp"
#endif
#include "effects/Strobe.cpp"

Effects::Effects(){
  this->reset();
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip.begin();
  strip.show();
}

void Effects::reset(){
  cConfig = 0;
  effect[0]  = &randomOn;
  cEffect[0] = RANDOM_ON;
  effect[1]  = &diffusion;
  cEffect[1] = DIFFUSION;
}

void Effects::run(EffectData &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    this->updateShouldStep(data);
    effect[0] -> run(sign, data);
    effect[1] -> run(sign, data);
    this -> updateStrip();
    this -> updateStrip(data);
    strip.show();
  }
}

void Effects::push(IrInput input, uint8_t layer){
  effect[layer]->push(input);
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

void Effects::setEffect(uint8_t kEffect, uint8_t layer){
  cEffect[layer] = kEffect;
  switch(kEffect){
    case NO_EFFECT: effect[layer] = &noEffect; break;
    case RANDOM_ON: effect[layer] = &randomOn; break;
  #if USE_SINGLE_FADE
    case SINGLE_FADE: effect[layer] = &singleFade; break;
  #endif
    case STROBE: effect[layer] = &strobe; break;
  #if USE_CENTER_SQUARE
    case CENTER_SQUARE: effect[layer] = &centerSquare; break;
  #endif
    case TWO_COLOR: effect[layer] = &twoColor; break;
    case WAVE0: effect[layer] = &wave0; break;
    case DIFFUSION: effect[layer] = &diffusion; break;
    case SPECTRUM_0: effect[layer] = &spectrum0; break;
  #if USE_WANDER
    case WANDER: effect[layer] = &wander; break;
  #endif
  #if USE_LINE_SPECTRUM
    case SPECTRUM_LINE: effect[layer] = &spectrumLine; break;
  #endif
    case CENTER_PULSE: effect[layer] = &centerPulse; break;
    case TIME_DOMAIN: effect[layer] = &timeDomain; break;
  #if USE_PARTICLE_SYSTEM
    case PARTICLE_SYSTEM: effect[layer] = &particleSystem; break;
  #endif
    case NEUMANN_AUTOMATA: effect[layer] = &neumannAutomata; break;
  }
  #ifdef DEBUG
    this->printEffect(kEffect);
  #endif
}

void Effects::setEffects(uint8_t textLayer, uint8_t colorLayer){
  this->setEffect(textLayer, TEXT_LAYER);
  this->setEffect(colorLayer, COLOR_LAYER);
}

#ifdef DEBUG
void Effects::printEffect(uint8_t kEffect){
  switch(kEffect){
    case RANDOM_ON: Serial.println("Random On"); break;
  #if USE_SINGLE_FADE
    case SINGLE_FADE: Serial.println("Single Fade"); break;
  #endif
    case TWO_COLOR: Serial.println("Two Color"); break;
    case STROBE: Serial.println("Strobe"); break;
    case CENTER_SQUARE: Serial.println("CenterSquare"); break;
    case WAVE0: Serial.println("Wave0"); break;
    case DIFFUSION: Serial.println("Diffusion"); break;
    case SPECTRUM_0: Serial.println("Spectrum0"); break;
  #if USE_WANDER
    case WANDER: Serial.println("Wander"); break;
  #endif
  #if USE_LINE_SPECTRUM
    case SPECTRUM_LINE: Serial.println("SpectrumLine");  break;
  #endif
    case CENTER_PULSE: Serial.println("CenterPulse"); break;
    case TIME_DOMAIN: Serial.println("TimeDomain"); break;
  #if USE_PARTICLE_SYSTEM
    case PARTICLE_SYSTEM: Serial.println("ParticleSystem"); break;
  #endif
    case NEUMANN_AUTOMATA: Serial.println("NeumannAutomata"); break;
  }
}
#endif

void Effects::setConfig(uint8_t kConfig){
  switch(kConfig){

    case FIRE0_CONFIG: this->setEffects(SPECTRUM_0, TWO_COLOR); break;

  #if USE_CENTER_SQUARE
    case SQUARE_0_CONFIG:
    case SQUARE_1_CONFIG:
      this->setEffects(CENTER_SQUARE, TWO_COLOR);
      break;
  #endif

    case STROBE_0_CONFIG:
    case STROBE_1_CONFIG:
    case STROBE_2_CONFIG:
      this->setEffects(STROBE, TWO_COLOR);
      break;

    case RANDOM_DIFFUSION_0_CONFIG: this->setEffect(RANDOM_ON, DIFFUSION); break;
    case THREE_COLOR_RANDOM_0_CONFIG: this->setEffects(RANDOM_ON, TWO_COLOR); break;

    case NEUMANN_0_CONFIG: this->setEffects(NEUMANN_AUTOMATA, TWO_COLOR); break;

  #if USE_PARTICLE_SYSTEM
    case PS_CENTER_FOUNTAIN:
    case PS_FIRE0_CONFIG:
      this->setEffects(NO_EFFECT, PARTICLE_SYSTEM);
      break;
  #endif

    case CENTER_WAVE_CONFIG: this->setEffects(CENTER_PULSE, WAVE0); break;

    case CENTER_SPECTRUM_CONFIG:
    case BOTTOM_BUBBLES_CONFIG: this->setEffects(SPECTRUM_LINE, WAVE0); break;

    case DIFFUSION_TIME_CONFIG: this->setEffects(TIME_DOMAIN, DIFFUSION); break;
  }
  effect[TEXT_LAYER]->setConfig(kConfig);
  effect[COLOR_LAYER]->setConfig(kConfig);
}

void Effects::nextEffect(uint8_t layer){
  cEffect[layer] = (++cEffect[layer]) % EFFECT_COUNT;
  this -> setEffect(cEffect[layer], layer);
}

void Effects::prevEffect(uint8_t layer){
  if(cEffect[layer] == 0){
    cEffect[layer] = EFFECT_COUNT - 1;
  }else{
    --cEffect[layer];
  }
  this -> setEffect(cEffect[layer], layer);
}

void Effects::nextConfig(){
  cConfig = (++cConfig) % CONFIG_COUNT;
  this -> setConfig(cConfig);
}

void Effects::prevConfig(){
  if(cConfig == 0){
    cConfig = CONFIG_COUNT - 1;
  }else{
    --cConfig;
  }
  this -> setConfig(cConfig);
}

void Effects::updateStrip(){
  uint8_t offset = 0;
  for(uint8_t idx = offset; idx< LED_COUNT; idx++){
    Pixel* pixel = sign.pixel(idx);
    strip.setPixelColor(idx-offset, pixel->color());
  }
}

void Effects::updateStrip(EffectData &data){
  if( data.pushLayer != CONFIG_LAYER){
    if(data.pushLayer == TEXT_LAYER){
      strip.setPixelColor(0, 0xFFFFFF);
    }else if( data.pushLayer == COLOR_LAYER){
      strip.setPixelColor(13, 0xFFFFFF);
    }else if( data.pushLayer == ADJUST_LAYER){
      strip.setPixelColor(14, 0xFFFFFF);
    }
  }
}
