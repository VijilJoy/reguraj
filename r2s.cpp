#include "r2s.h"

const boolean input[4][3] PROGMEM = { { 0, 1, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0, 0, 0 } };  //  Input Selector
const boolean rec_out[4][2] PROGMEM = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };            //  REC-Output Gain Control
const boolean input_att[4][2] PROGMEM = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };          //ADC Input ATT

const boolean bass_data[16][4] PROGMEM = { { 1, 1, 1, 1 }, { 1, 1, 1, 0 }, { 1, 1, 0, 1 }, { 1, 1, 0, 0 }, { 1, 0, 1, 1 }, { 1, 0, 1, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 1, 0 }, { 0, 0, 1, 1 }, { 0, 1, 0, 0 }, { 0, 1, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1, 1, 1 }, { 0, 0, 0, 0 } };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    // bass
const boolean treb_data[16][4] PROGMEM = { { 1, 1, 1, 1 }, { 1, 1, 1, 0 }, { 1, 1, 0, 1 }, { 1, 1, 0, 0 }, { 1, 0, 1, 1 }, { 1, 0, 1, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 1, 0 }, { 0, 0, 1, 1 }, { 0, 1, 0, 0 }, { 0, 1, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1, 1, 1 }, { 0, 0, 0, 0 } };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    // treble
const boolean input_gain_data[8][3] PROGMEM = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       //Input Gain
const boolean input_control_data[8][3] PROGMEM = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    //Gain Control
const boolean volume[100][7] PROGMEM = { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0, 1, 1 }, { 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0, 1 }, { 0, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 1, 1, 1 }, { 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 1 }, { 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 1, 0, 1, 1 }, { 0, 0, 0, 1, 1, 0, 0 }, { 0, 0, 0, 1, 1, 0, 1 }, { 0, 0, 0, 1, 1, 1, 0 }, { 0, 0, 0, 1, 1, 1, 1 }, { 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 1, 1 }, { 0, 0, 1, 0, 1, 0, 0 }, { 0, 0, 1, 0, 1, 0, 1 }, { 0, 0, 1, 0, 1, 1, 0 }, { 0, 0, 1, 0, 1, 1, 1 }, { 0, 0, 1, 1, 0, 0, 0 }, { 0, 0, 1, 1, 0, 0, 1 }, { 0, 0, 1, 1, 0, 1, 0 }, { 0, 0, 1, 1, 0, 1, 1 }, { 0, 0, 1, 1, 1, 0, 0 }, { 0, 0, 1, 1, 1, 0, 1 }, { 0, 0, 1, 1, 1, 1, 0 }, { 0, 0, 1, 1, 1, 1, 1 }, { 0, 1, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 1, 0, 1 }, { 0, 1, 0, 0, 1, 1, 0 }, { 0, 1, 0, 0, 1, 1, 1 }, { 0, 1, 0, 1, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 1 }, { 0, 1, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 1, 1 }, { 0, 1, 0, 1, 1, 0, 0 }, { 0, 1, 0, 1, 1, 0, 1 }, { 0, 1, 0, 1, 1, 1, 0 }, { 0, 1, 0, 1, 1, 1, 1 }, { 0, 1, 1, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0, 0, 1 }, { 0, 1, 1, 0, 0, 1, 0 }, { 0, 1, 1, 0, 0, 1, 1 }, { 0, 1, 1, 0, 1, 0, 0 }, { 0, 1, 1, 0, 1, 0, 1 }, { 0, 1, 1, 0, 1, 1, 0 }, { 0, 1, 1, 0, 1, 1, 1 }, { 0, 1, 1, 1, 0, 0, 0 }, { 0, 1, 1, 1, 0, 0, 1 }, { 0, 1, 1, 1, 0, 1, 0 }, { 0, 1, 1, 1, 0, 1, 1 }, { 0, 1, 1, 1, 1, 0, 0 }, { 0, 1, 1, 1, 1, 0, 1 }, { 0, 1, 1, 1, 1, 1, 0 }, { 0, 1, 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 1, 1 }, { 1, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 1, 0, 1 }, { 1, 0, 0, 0, 1, 1, 0 }, { 1, 0, 0, 0, 1, 1, 1 }, { 1, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 1, 0, 0, 1 }, { 1, 0, 0, 1, 0, 1, 0 }, { 1, 0, 0, 1, 0, 1, 1 }, { 1, 0, 0, 1, 1, 0, 0 }, { 1, 0, 0, 1, 1, 0, 1 }, { 1, 0, 0, 1, 1, 1, 0 }, { 1, 0, 0, 1, 1, 1, 1 }, { 1, 0, 1, 0, 0, 0, 0 }, { 1, 0, 1, 0, 0, 0, 1 }, { 1, 0, 1, 0, 0, 1, 0 }, { 1, 0, 1, 0, 0, 1, 1 }, { 1, 0, 1, 0, 1, 0, 0 }, { 1, 0, 1, 0, 1, 0, 1 }, { 1, 0, 1, 0, 1, 1, 0 }, { 1, 0, 1, 0, 1, 1, 1 }, { 1, 0, 1, 1, 0, 0, 0 }, { 1, 0, 1, 1, 0, 0, 1 }, { 1, 0, 1, 1, 0, 1, 0 }, { 1, 0, 1, 1, 0, 1, 1 }, { 1, 0, 1, 1, 1, 0, 0 }, { 1, 0, 1, 1, 1, 0, 1 }, { 1, 0, 1, 1, 1, 1, 0 }, { 1, 0, 1, 1, 1, 1, 1 }, { 1, 1, 0, 0, 0, 0, 0 }, { 1, 1, 0, 0, 0, 0, 1 }, { 1, 1, 0, 0, 0, 1, 0 }, { 1, 1, 0, 0, 0, 1, 1 } };  // volume

void initR2s() {
  pinMode(DATA_PIN_R2S, OUTPUT);
  pinMode(CLK_PIN_R2S, OUTPUT);
}

void writeToAudioSlot1(int in, int out_gain, int att, bool R_L_in, int bass, int treb, int in_gain, bool toneEnable) {
  // input selector  ||  0-2 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input[in][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  //  REC Output  ||  3 bit
  digitalWrite(DATA_PIN_R2S, HIGH);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  //  REC-Output Gain Control  ||  4-5 bit
  for (int i = 0; i < 2; i++) {
    digitalWrite(DATA_PIN_R2S, rec_out[out_gain][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  //  ADC Input ATT  ||  6-7 bit
  for (int i = 0; i < 2; i++) {
    digitalWrite(DATA_PIN_R2S, input_att[att][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  //   L/R Input   || 8 bit
  digitalWrite(DATA_PIN_R2S, R_L_in);  // 0 ... 1
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // BASS  ||   9 - 12 bit
  for (int i = 0; i < 4; i++) {
    digitalWrite(DATA_PIN_R2S, toneEnable ? bass_data[bass][i] : bass_data[16][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // TREBLE   ||  13 - 16 bit
  for (int i = 0; i < 4; i++) {
    digitalWrite(DATA_PIN_R2S, toneEnable ? treb_data[treb][i] : bass_data[16][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  //   SL/ SR/ C/ SW Input  || 17 bit
  digitalWrite(DATA_PIN_R2S, R_L_in);  // 0 IN Stereo / 1 IN 5.1
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // Input Gain  ||  18 - 20 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_gain_data[in_gain][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // 21 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 22 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 23 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, HIGH);  // CLOCK
  digitalWrite(CLK_PIN_R2S, LOW);
  digitalWrite(DATA_PIN_R2S, LOW);
}

void writeToAudioSlot2(int gain0, int vol0, int gain1, int vol1) {
  // Gain Control 0  ||  0-2 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_control_data[gain0][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // volume 0  ||  3 - 9 bit
  for (int i = 0; i < 7; i++) {
    digitalWrite(DATA_PIN_R2S, volume[vol0][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // Gain Control 1  ||  10-12 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_control_data[gain1][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // volume 1  ||  13 - 19 bit
  for (int i = 0; i < 7; i++) {
    digitalWrite(DATA_PIN_R2S, volume[vol1][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  //  20 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  //  21 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 22 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 23 bit
  digitalWrite(DATA_PIN_R2S, HIGH);  // 1
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, HIGH);  // CLOCK
  digitalWrite(CLK_PIN_R2S, LOW);
  digitalWrite(DATA_PIN_R2S, LOW);
}

void writeToAudioSlot3(int gain2, int vol2, int gain3, int vol3) {
  // Gain Control 2  ||  0-2 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_control_data[gain2][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // volume 2  ||  3 - 9 bit
  for (int i = 0; i < 7; i++) {
    digitalWrite(DATA_PIN_R2S, volume[vol2][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // Gain Control 3  ||  10-12 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_control_data[gain3][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // volume 3  ||  13 - 19 bit
  for (int i = 0; i < 7; i++) {
    digitalWrite(DATA_PIN_R2S, volume[vol3][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // 20 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  //  21 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 22 bit LOW
  digitalWrite(DATA_PIN_R2S, HIGH);  // 1
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 23 bit  HIGH
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, HIGH);  // CLOCK
  digitalWrite(CLK_PIN_R2S, LOW);
  digitalWrite(DATA_PIN_R2S, LOW);
}

void writeToAudioSlot4(int gain4, int vol4, int gain5, int vol5) {
  // Gain Control 4  ||  0-2 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_control_data[gain4][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // volume 4  ||  3 - 9 bit
  for (int i = 0; i < 7; i++) {
    digitalWrite(DATA_PIN_R2S, volume[vol4][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // Gain Control 5  ||  10-12 bit
  for (int i = 0; i < 3; i++) {
    digitalWrite(DATA_PIN_R2S, input_control_data[gain5][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // volume 5  ||  13 - 19 bit
  for (int i = 0; i < 7; i++) {
    digitalWrite(DATA_PIN_R2S, volume[vol5][i]);
    digitalWrite(CLK_PIN_R2S, HIGH);
    digitalWrite(DATA_PIN_R2S, LOW);
    digitalWrite(CLK_PIN_R2S, LOW);
  }
  // 20 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  //  21 bit
  digitalWrite(DATA_PIN_R2S, LOW);  // 0
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 22 bit LOW
  digitalWrite(DATA_PIN_R2S, HIGH);  // 1
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, LOW);
  digitalWrite(CLK_PIN_R2S, LOW);
  // 23 bit  HIGH
  digitalWrite(DATA_PIN_R2S, HIGH);  // 1
  digitalWrite(CLK_PIN_R2S, HIGH);
  digitalWrite(DATA_PIN_R2S, HIGH);  // CLOCK
  digitalWrite(CLK_PIN_R2S, LOW);
  digitalWrite(DATA_PIN_R2S, LOW);
}
