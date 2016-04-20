#include "CenterSquare.h"

CenterSquare::CenterSquare(){
  perTempo = 2;
  lookDistance = 1;
  isOffCycle = false;
  lookDistanceCount = 0;
}

void CenterSquare::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();
  if(data.volume > mVolume){ mVolume = data.volume;}
  if( currMillis - lastStep < data.tempo/perTempo ) { return; }
  lastStep = currMillis;
  data.shouldStep = true;

  if(isOffCycle){
    sign.setDirection(Off);
    isOffCycle = false;
  }

  if((settingsMask & IS_CYCLE_LOOK_DIST) > 0){
    lookDistanceCount++;
    if(lookDistanceCount > perTempo*2){
      lookDistance = (lookDistance++) % LOOK_DISTANCE_MAX+1;
      lookDistanceCount = 0;
    }
  }

  sign.push();
  this->setCenter(sign, data);

  for(uint8_t i=0; i<LED_WIDTH; i++){
    for(uint8_t j=0; j<LED_HEIGHT; j++){
      if(i == LED_X_CENTER && j == LED_Y_CENTER){ continue;}
      if((settingsMask & IS_SQUARE_1) > 0){
        this -> square1(sign, i, j);
      }else{
        this -> square0(sign, i, j);
      }
    }
  }
  mVolume = 0;

}

void CenterSquare::setCenter(Sign &sign, EffectData &data){
  Pixel* pixel = sign.pixel(3,2);

  if( (settingsMask & IS_USING_SOUND) > 0 ){

    if(mVolume < data.maxVolume/4){
      pixel->direction[0] = Off;
    }else if(mVolume < data.maxVolume/2){
      pixel->direction[0] = Down;
    }else{
      pixel->direction[0] = Up;
    }

  }else{

    Direction newD = pixel -> direction[0];

    switch(newD){
      case Down: newD = Off; break;
      case Off: newD = Up; break;
      case Up: newD = Down; break;
    }
    pixel->direction[0] = newD;

  }
}

void CenterSquare::square0(Sign &sign, uint8_t x, uint8_t y){

  Pixel *pixel = sign.pixel(x,y);
  Direction currDirection = pixel->direction[1];

  uint8_t ld = lookDistance;

  if(x < LED_X_CENTER && y < LED_Y_CENTER){ //Lower Left
         if(this->updatePixel(pixel, sign.pixel(x+ld, y   ) )){}
    else if(this->updatePixel(pixel, sign.pixel(x   , y+ld) )){}
    else if(this->updatePixel(pixel, sign.pixel(x+ld, y+ld) )){}

  }else if( x < LED_X_CENTER){ // Upper Left
         if(this->updatePixel(pixel, sign.pixel(x+ld, y   ) )){}
    else if(this->updatePixel(pixel, sign.pixel(x   , y-ld) )){}
    else if(this->updatePixel(pixel, sign.pixel(x+ld, y-ld) )){}

  }else if( y < LED_Y_CENTER ){ // Lower Right
         if(this->updatePixel(pixel, sign.pixel(x-ld, y   ) )){}
    else if(this->updatePixel(pixel, sign.pixel(x   , y+ld) )){}
    else if(this->updatePixel(pixel, sign.pixel(x-ld, y+ld) )){}

  }else{ //Upper Right
         if(this->updatePixel(pixel, sign.pixel(x-ld, y   ) )){}
    else if(this->updatePixel(pixel, sign.pixel(x   , y-ld) )){}
    else if(this->updatePixel(pixel, sign.pixel(x-ld, y-ld) )){}
  }

}

void CenterSquare::square1(Sign &sign, uint8_t x, uint8_t y){

  Pixel *pixel = sign.pixel(x,y);
  Direction currDirection = pixel->direction[1];
  uint8_t ld = lookDistance;

  if(x < LED_X_CENTER && y < LED_Y_CENTER){ //Lower Left
    this->updatePixel(pixel, sign.pixel(x+ld, y+ld));
    //this->updatePixel(pixel, sign.pixel(x+ld, y));
  }else if( x < LED_X_CENTER && y > LED_Y_CENTER){ // Upper Left
    this->updatePixel(pixel, sign.pixel(x+ld, y-ld));
    //this->updatePixel(pixel, sign.pixel(x+ld, y));
  }else if( x > LED_X_CENTER && y < LED_Y_CENTER){ // Lower Right
    this->updatePixel(pixel, sign.pixel(x-ld, y+ld));
    //this->updatePixel(pixel, sign.pixel(x-ld, y));
  }else if( x > LED_X_CENTER && y > LED_Y_CENTER){ //Upper Right
    this->updatePixel(pixel, sign.pixel(x-ld, y-ld));
    //this->updatePixel(pixel, sign.pixel(x, y-ld));

  }else if( x == LED_X_CENTER && y > LED_Y_CENTER){
    this->updatePixel(pixel, sign.pixel(x, y-ld));
  }else if( x == LED_X_CENTER && y < LED_Y_CENTER){
    this->updatePixel(pixel, sign.pixel(x, y+ld));
  }else if( x > LED_X_CENTER && y == LED_Y_CENTER){
    this->updatePixel(pixel, sign.pixel(x-ld, y));
  }else if( x < LED_X_CENTER && y == LED_Y_CENTER){
    this->updatePixel(pixel, sign.pixel(x+ld, y));
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
  switch(input){
    case UP:   if(perTempo < MAX_PER_TEMPO){ perTempo++; } break;
    case DOWN: if(perTempo > 0){ perTempo--; }; break;
    case RIGHT:
                 settingsMask = ++settingsMask % CENTER_SQUARE_SETTING_COUNT;
                 break;
    case LEFT:
                 lookDistance = (lookDistance++) % LOOK_DISTANCE_MAX+1;
                 break;
    case CENTER:
                 isOffCycle = true;
                 break;

  }
  //if((settingsMask & IS_SQUARE_1) > 0){
    //Serial.println("SQUARE 1");
  //}else{
    //Serial.println("SQUARE 0");
  //}

  //if((settingsMask & IS_USING_SOUND) >0){
    //Serial.println("SOUND");
  //}else{
    //Serial.println("NO SOUND");
  //}
}

void CenterSquare::setConfig(uint8_t kConfig){
  perTempo = 1;
  settingsMask = 0;
  lookDistance = 1;

  switch(kConfig){

    case SQUARE_0_CONFIG:
      perTempo = 3;
      settingsMask = IS_SQUARE_1 | IS_USING_SOUND;
      break;

    case SQUARE_1_CONFIG:
      perTempo = 2;
      lookDistance = 1;
      settingsMask = IS_CYCLE_LOOK_DIST | IS_USING_SOUND;
      break;

  }
}


