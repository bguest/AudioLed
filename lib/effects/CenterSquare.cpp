#include "CenterSquare.h"

CenterSquare::CenterSquare(){
  perTempo = 2;
}

void CenterSquare::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();
  if(data.volume > mVolume){ mVolume = data.volume;}
  if( currMillis - lastStep < data.tempo/perTempo ) { return; }
  lastStep = currMillis;
  data.shouldStep = true;

  sign.push();
  this->setCenter(sign, data);

  for(uint8_t i=0; i<LED_WIDTH; i++){
    for(uint8_t j=0; j<LED_WIDTH; j++){
      this->squareize(sign, i, j);
    }
  }
  mVolume = 0;

}

void CenterSquare::setCenter(Sign &sign, EffectData &data){
  Pixel* pixel = sign.pixel(3,2);

  //Direction newD = pixel -> direction[0];

  //switch(newD){
    //case Down: newD = Off; break;
    //case Off: newD = Up; break;
    //case Up: newD = Down; break;
  //}
  //pixel->direction[0] = newD;

  //Serial.print("\n\r MAX:");
  //Serial.print(data.maxVolume);
  //Serial.print("\n\r VOLUME:");
  //Serial.print(mVolume);

  if(mVolume < data.maxVolume/4){
    pixel->direction[0] = Off;
  }else if(mVolume < data.maxVolume/2){
    pixel->direction[0] = Down;
  }else{
    pixel->direction[0] = Up;
  }
}

void CenterSquare::squareize(Sign &sign, uint8_t x, uint8_t y){
  if(x == 3 && y ==2){ return; }

  Pixel *pixel = sign.pixel(x,y);
  Direction currDirection = pixel->direction[1];

  if(x < LED_WIDTH/2 && y < LED_HEIGHT/2){ //Lower Left
          if(this->updatePixel(pixel, sign.pixel(x+1, y+1) )){
    }else if(this->updatePixel(pixel, sign.pixel(x+1, y  ) )){
    }else if(this->updatePixel(pixel, sign.pixel(x  , y+1) )){}
  }else if( x < LED_WIDTH/2 ){ // Upper Left
          if(this->updatePixel(pixel, sign.pixel(x+1, y-1) )){
    }else if(this->updatePixel(pixel, sign.pixel(x+1, y  ) )){
    }else if(this->updatePixel(pixel, sign.pixel(x  , y-1) )){}

  }else if( y < LED_HEIGHT/2 ){ // Lower Right
          if(this->updatePixel(pixel, sign.pixel(x-1, y+1) )){
    }else if(this->updatePixel(pixel, sign.pixel(x-1, y  ) )){
    }else if(this->updatePixel(pixel, sign.pixel(x  , y+1) )){}

  }else{ //Upper Right
          if(this->updatePixel(pixel, sign.pixel(x-1, y-1) )){
    }else if(this->updatePixel(pixel, sign.pixel(x-1, y  ) )){
    }else if(this->updatePixel(pixel, sign.pixel(x  , y-1) )){}

  }

}

bool CenterSquare::updatePixel(Pixel *target, Pixel *source){
  if(target->direction[1] != source->direction[1]){
    target->direction[0] = source->direction[1];
    return true;
  }else{
    return false;
  }
}

void CenterSquare::push(IrInput input){
  Effect::push(input);
  switch(input){
    case UP:   if(perTempo < MAX_PER_TEMPO){ perTempo++; } break;
    case DOWN: if(perTempo > 0){ perTempo--; }; break;
  }
}

void CenterSquare::setConfig(uint8_t kConfig){
  switch(kConfig){
    case SQUARE_0_CONFIG: perTempo = 1; break;
  }
}


