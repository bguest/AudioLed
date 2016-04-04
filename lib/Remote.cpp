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
    case PLAY_PAUSE_IR_0: case PLAY_PAUSE_IR_1: return PLAY_PAUSE;
    case MENUE_IR_0:      case MENUE_IR_1:      return MENUE;
    case UP_IR_0:         case UP_IR_1:         return UP;
    case DOWN_IR_0:       case DOWN_IR_1:       return DOWN;
    case LEFT_IR_0:       case LEFT_IR_1:       return LEFT;
    case RIGHT_IR_0:      case RIGHT_IR_1:      return RIGHT;
    case CENTER_IR_0:     case CENTER_IR_1:     return CENTER;
  }
  return NONE;
}

