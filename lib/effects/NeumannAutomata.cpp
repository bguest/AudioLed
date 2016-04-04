#include "NeumannAutomata.h"

NeumannAutomata::NeumannAutomata(){
  kRule = 0;
}

void NeumannAutomata::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return; }
  sign.pixel(0,0)->direction[0] = Up;
  sign.push();

  for(uint8_t i = 0; i<LED_WIDTH; i++){
    for(uint8_t j = 0; j<LED_HEIGHT; j++){
      uint32_t state = this->neighborhoodState(sign, i,j);
      Pixel* pixel = sign.pixel(i,j);
      this->setPixel(pixel, state);
    }
  }
}

uint8_t NeumannAutomata::neighborhoodState(Sign &sign, uint8_t x, uint8_t y){
  uint8_t state = 0b00000;
  if(sign.pixel(x,y)->direction[1] == Up){
    state |= 0b10000;
  }

  if(x < LED_HEIGHT-1 && sign.pixel(x+1,y)->direction[1] == Up){
    state |= 0b01000;
  }

  if(y < LED_WIDTH-1 && sign.pixel(x, y+1)->direction[1] == Up){
    state |= 0b00100;
  }

  if(x >= 0  && sign.pixel(x-1, y)->direction[1] == Up){
    state |= 0b00010;
  }

  if(y >= 0  && sign.pixel(x, y-1)->direction[1] == Up){
    state |= 0b00001;
  }
  return state;
}

#define RULE_COUNT 4

void NeumannAutomata::setPixel(Pixel *pixel, uint8_t state){

                 //0---------1---------2---------3--
                 //012345678901234567890123456789012
  uint32_t key = 0b10000000000000000000000000000000;
  uint32_t rule;

  switch(kRule){
    case 0:
           //0---------1---------2---------3--
           //012345678901234567890123456789012
    rule = 0b11111111111111111111111111111111;
    break;

    case 1:  //Fredkin2
           //0---------1---------2---------3--
           //012345678901234567890123456789012
    rule = 0b01101001100101101001011001101001;
    break;

    case 2: //Crystal2
           //0---------1---------2---------3--
           //012345678901234567890123456789012
    rule = 0b01101101101101101111101011001000;
    break;

    case 3:
    default:
           //0---------1---------2---------3--
           //012345678901234567890123456789012
    rule = 0b00000000000000000000000000000000;
    break;


  }

  if( rule & (key >> state) ){
    pixel->direction[0] = Up;
  }else{
    pixel->direction[0] = Off;
  }
}

void NeumannAutomata::push(IrInput input){
  Effect::push(input);

  switch(input){
    case UP: if(kRule < RULE_COUNT){ ++kRule;} break;
    case DOWN: if(kRule > 0){ --kRule;} break;
  }
}

void NeumannAutomata::setConfig(uint8_t kConfig){
  switch(kConfig){
    case NEUMANN_0_CONFIG:
      kRule = 1;
      break;
  }
}


