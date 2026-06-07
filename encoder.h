#include "controllers.h"
#ifndef ENCODER_H
#define ENCODER_H

#define ENC_A PB1
#define ENC_B PB0
#define ENC_S PB2

extern volatile bool enc_a, enc_b, enc_x, enc_y;
extern bool enc_s;
extern unsigned long int sw_timer;
extern bool long_pressed;

void enc_switch();
void encoder_init(void);
void enc_task(void);
void PinInterrupt_ISR();

#endif