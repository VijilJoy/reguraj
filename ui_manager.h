#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "big_font.h"
#include "global.h"
#include <Arduino.h>

extern bool started_up;
extern uint32_t stb_timer;
extern unsigned long int backlight_timer;
extern bool timer_overflow;
extern bool pow_led_state;

void ui_init();
void ui_task();
void show_stb_mode();
void show_name_editor();
void show_gain_menu();
void display_home_menu();
void display_value(char num);
void print_big_num(char n,char x);
void print_mute();

#endif