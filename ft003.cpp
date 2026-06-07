#include "ft003.h"
#include "global.h"

void ft003_init(){
    pinMode(pinA,OUTPUT);
    pinMode(pinB,OUTPUT);

    digitalWrite(pinA,0);
    digitalWrite(pinB,0);
  }
void ft003_setMode(uint8_t mode){
  switch(mode){
    case ARC_IN:
    digitalWrite(pinA,0);
    digitalWrite(pinB,0);
    break;

    case OPT_IN:
    digitalWrite(pinA,0);
    digitalWrite(pinB,1);
    break;

    case COAX_IN:
    digitalWrite(pinA,1);
    digitalWrite(pinB,0);
    break;

    default:
    digitalWrite(pinA,1);
    digitalWrite(pinB,1);
    break;
  };
  }