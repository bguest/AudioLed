#include "Effect.h"

Effect::Effect(){
}

void Effect::run(Sign &sign, EffectData &data){
}

void Effect::push(IrInput input){
  if(input == CENTER){
    this->randomize();
  }
}

void Effect::setConfig(uint8_t kConfig){
}

void Effect::randomize(){
}

