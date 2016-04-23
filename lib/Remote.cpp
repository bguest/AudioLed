#include "Remote.h"

Remote::Remote(){
  irrecv = new IRrecv(IR_PIN);
  code = NONE;
  isRepeat = false;
}

void Remote::init(){
  irrecv -> enableIRIn();
}

void Remote::run(){
  if (irrecv -> decode(&irResults)) {
    uint8_t value = (irResults.value & 0x00FF00) >> 8;
    if(value == REPEAT_IR){
      isRepeat = true;
    }else if(value != SECOND_IR){
      code = this->inputFromIrCode(value);
      isRepeat = false;
    }
    irrecv -> resume(); // Receive the next value
  }else{
    code = NONE;
  }
}

IrInput Remote::inputFromIrCode(uint8_t irCode){
  switch(irCode){
    case PLAY_PAUSE_IR:  return PLAY_PAUSE;
    case MENUE_IR:       return MENUE;
    case UP_IR:          return UP;
    case DOWN_IR:        return DOWN;
    case LEFT_IR:        return LEFT;
    case RIGHT_IR:       return RIGHT;
    case CENTER_IR:      return CENTER;
  }
  return NONE;
}

