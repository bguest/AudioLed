#ifndef REMOTE_H
#define REMOTE_H

#include "Arduino.h"
#include "IRremote.h"

#define IR_PIN A3
#define PLAY_PAUSE_IR 0x31F0E936
#define MENUE_IR      0xD14F58B0
#define UP_IR         0x17E1F858
#define DOWN_IR       0x8EBB3CFC
#define LEFT_IR       0xC26B4710
#define RIGHT_IR      0xFA0E2992
#define CENTER_IR     0x133620BA

typedef enum _irInput{
  UP = 0, RIGHT, DOWN, LEFT, CENTER, PLAY_PAUSE, MENUE, NONE
} IrInput;

class Remote{

  public:
    Remote();
    void init();
    void run();
    IrInput code;

  private:
    IRrecv *irrecv;
    decode_results irResults;
    IrInput inputFromIrCode(uint32_t irCode);
    void handleIrCode(uint32_t irCode);
};

#endif
