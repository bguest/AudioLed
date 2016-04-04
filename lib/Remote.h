#ifndef REMOTE_H
#define REMOTE_H

#include "Arduino.h"
#include "IRremote.h"

#define IR_PIN A3

#define PLAY_PAUSE_IR_0 0x31F0E936
#define PLAY_PAUSE_IR_1 0xFFF18C59
#define MENUE_IR_0      0xD14F58B0
#define MENUE_IR_1      0x5F00BA93
#define UP_IR_0         0x17E1F858
#define UP_IR_1         0xA5935A3B
#define DOWN_IR_0       0x8EBB3CFC
#define DOWN_IR_1       0x1C6C9EDF
#define LEFT_IR_0       0xC26B4710
#define LEFT_IR_1       0x501CA8F3
#define RIGHT_IR_0      0xFA0E2992
#define RIGHT_IR_1      0xC80ECCB5
#define CENTER_IR_0     0x133620BA
#define CENTER_IR_1     0xE136C3DD

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
