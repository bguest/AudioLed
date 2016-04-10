#include "Strobe.h"

const uint8_t MAX_PER_TEMPO = 30;

Strobe::Strobe(){
  perTempo = 2;
}

void Strobe::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();
  if( currMillis - lastStep < data.tempo/perTempo ) { return; }
  lastStep = currMillis;
  data.shouldStep = true;

  Direction newD = sign.pixel(0) -> direction[0];

  switch(newD){
    case Down: newD = Off; break;
    case Off: newD = Up; break;
    case Up: newD = Down; break;
  }

  for(uint8_t i=0; i<LED_COUNT; i++){
    sign.pixel(i) -> direction[0] = newD;
  }

}

void Strobe::push(IrInput input){
  Effect::push(input);
  switch(input){
    case UP:   if(perTempo < MAX_PER_TEMPO){ perTempo++; } break;
    case DOWN: if(perTempo > 0){ perTempo--; }; break;
  }
}

void Strobe::setConfig(uint8_t kConfig){
  switch(kConfig){
    case STROBE_1_CONFIG:
    case STROBE_0_CONFIG: perTempo = 16; break;
  }
}

