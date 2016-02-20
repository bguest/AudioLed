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

void Effect::randomize(){
}

