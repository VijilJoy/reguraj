#ifndef NEC_IR_H
#define NEC_IR_H

#include "controllers.h"

#define IR_RECEIVE_PIN PB10
#define IR_SEND_PIN PB11 // IR LED connected here
#define USE_NO_SEND_PWM

#define IR_EMIT_MODE       0xE51A7F80
#define IR_EMIT_MUTE       0xE11E7F80
#define IR_EMIT_BACKW      0xFD027F80
#define IR_EMIT_FWD        0xFC037F80
#define IR_EMIT_PLAY_PAUSE 0xFE017F80
#define IR_EMIT_VOL_MINUS  0xFA057F80
#define IR_EMIT_VOL_PLUS   0xF9067F80
#define IR_EMIT_EQ         0xFB047F80
#define IR_EMIT_0          0xF8077F80
#define IR_EMIT_1          0xF50A7F80
#define IR_EMIT_2          0xE41B7F80
#define IR_EMIT_3          0xE01F7F80
#define IR_EMIT_4          0xF30C7F80
#define IR_EMIT_5          0xF20D7F80
#define IR_EMIT_6          0xF10E7F80
#define IR_EMIT_7          0xFF007F80
#define IR_EMIT_8          0xF00F7F80
#define IR_EMIT_9          0xE6197F80

#define POWER      0xBE41
#define MUTE       0xBD42
#define USB        0xB946
#define SD_FM      0xBA45
#define SAVE_R	   0xB748
#define PRO 	     0xBF40
#define AUX        0xBB44 
#define DVD        0xFB04
#define AUTO       0xB54A
#define TUNE_PLUS  0xB649
#define TUNE_MINU  0xF20D
#define CH_PLUS    0xB34C
#define CH_MINU    0xB14E
#define PLAY_PAUS  0xB24D
#define SLEEP_MIN  0xF00F
#define SLEEP_PLU  0xF30C
#define FL_MINU    0xFC03
#define FL_PLUS    0xFD02
#define FR_PLUS    0xFF00
#define FR_MINU    0xFE01
#define SW_PLUS    0xF40B
#define SW_MINU    0xF807
#define CEN_PLUS   0xF50A
#define CEN_MINU   0xF906
#define VOL_PLUS   0xF609
#define VOL_MINU   0xFA05
#define SL_MINU    0xEC13
#define SL_PLUS    0xED12
#define SR_MINU    0xEE11
#define SR_PLUS    0xEF10
#define ZERO       0xA659
#define ONE        0xAD52
#define TWO        0xAE51
#define THREE      0xAF50
#define FOUR       0xE817
#define FIVE       0xE916
#define SIX        0xEA15
#define SEVEN      0xA956
#define EIGHT      0xAA55
#define NINE       0xAB54
#define REPEAT     0xA55A
#define RESET      0xA758
#define EQ_M       0xE41B
#define EQ_P       0xE51A
#define DIS_M      0xE619
#define DIS_P      0xE718


void handleKeyAction(uint16_t key);
void ir_task(void);
void IR_RemoteInit(void);

#endif