#include "Wander.h"

Wander::Wander(){
  x = floor(LED_WIDTH/2);
  y = floor(LED_HEIGHT/2);
  keepOn = false;
}

void Wander::run(Sign &sign, EffectData &data){
  if(!data.shouldStep){ return;}

  if(!keepOn || !this->canMove(sign)){
    sign.off();
  }

  uint8_t newX = 255;
  uint8_t newY = 255;

  while(!this->valid(newX, newY, sign)){
    newX = x;
    newY = y;
    this -> get(random(4), newX, newY);
    //Serial.print(newY);
    //Serial.print(' ');
    //Serial.print(newX);
    //Serial.print('\n');
  }

  x = newX;
  y = newY;

  Pixel* pixel = sign.pixel(x,y);
  pixel->isOn = true;

}

bool Wander::canMove(Sign &sign){
  for(uint8_t i=0; i<4; i++){
    uint8_t newX;
    uint8_t newY;
    this->get(i, newX, newY);
    if(this->valid(newX, newY, sign)){
      return true;
    }
  }
  return false;
}

bool Wander::valid(uint8_t newX, uint8_t newY, Sign& sign){


  if(newX >= LED_WIDTH){ return false;}
  if(newY >= LED_HEIGHT){ return false;}

  Pixel* pixel = sign.pixel(newX, newY);
  if(pixel-> isOn){ return false; }

  return true;
}

void Wander::get(uint8_t direction, uint8_t &newX, uint8_t &newY){
  switch(direction){
    case 0: newX = x+1; newY = y; return;
    case 1: newX = x; newY = y+1; return;
    case 2: newX = x-1; newY = y; return;
    case 3: newX = x; newY = y-1; return;
  }

}
