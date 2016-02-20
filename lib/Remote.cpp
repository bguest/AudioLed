#include "Remote.h"

Remote::Remote(){
  irrecv = new IRrecv(IR_PIN);
  code = NONE;
}

void Remote::init(){
  irrecv -> enableIRIn();
}

void Remote::run(){
  if (irrecv -> decode(&irResults)) {
    code = this->inputFromIrCode(irResults.value);
    irrecv -> resume(); // Receive the next value
  }else{
    code = NONE;
  }
}

IrInput Remote::inputFromIrCode(uint32_t irCode){
  switch(irCode){
    case PLAY_PAUSE_IR: return PLAY_PAUSE;
    case MENUE_IR:      return MENUE;
    case UP_IR:         return UP;
    case DOWN_IR:       return DOWN;
    case LEFT_IR:       return LEFT;
    case RIGHT_IR:      return RIGHT;
    case CENTER_IR:     return CENTER;
  }
  return NONE;
}

