#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>

#define DATA_PIN_R2S PB4  // R2s
#define CLK_PIN_R2S PB5   //  R2s

void initR2s();
void writeToAudioSlot1(int in, int out_gain, int att, bool R_L_in, int bass, int treb, int in_gain, bool toneEnable);
void writeToAudioSlot2(int gain0, int vol0, int gain1, int vol1);
void writeToAudioSlot3(int gain2, int vol2, int gain3, int vol3);
void writeToAudioSlot4(int gain4, int vol4, int gain5, int vol5);

#endif
