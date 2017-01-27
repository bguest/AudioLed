#ifndef REMOTE_H
#define REMOTE_H

#include "Arduino.h"
#include "IRremote.h"

// Requires Arduino-IRremote DECODE_NEC 1

#define IR_PIN A3

#define PLAY_PAUSE_IR 0x7A
#define MENUE_IR      0x40
#define UP_IR         0xD0
#define DOWN_IR       0xB0
#define RIGHT_IR      0xE0
#define LEFT_IR       0x10
#define CENTER_IR     0xBA
#define REPEAT_IR     0xFF
#define SECOND_IR     0x20

typedef enum _irInput{
  UP = 0, RIGHT, DOWN, LEFT, CENTER, PLAY_PAUSE, MENUE, NONE
} IrInput;

class Remote{

  public:
    Remote();
    void init();
    void run();
    IrInput code;
    bool isRepeat;

  private:
    IRrecv *irrecv;
    decode_results irResults;
    IrInput inputFromIrCode(uint8_t irCode);
};

#endif
