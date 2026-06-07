#ifndef TDA_H
#define TDA_H

void writeWire(char id, char a, char b);
void tda_set_input(char input);
void tda_set_gain(char gain);
void tda_set_volume(char volume);
void tda_set_tone(char range,char val);
void tda_mute();
void tda_set_ch_volume(char id, int att_r, int att_l);

#endif	