#ifndef lcd_h
#define lcd_h
#include "global.h"
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void lcd_print(const char * str);
void lcd_print(const unsigned char * str);
void lcd_data(unsigned char dt, int r);
void lcd_crt_chr (unsigned char loc, const unsigned char *msg);
void lcd_backlight(bool on);
void lcd_init();
void lcd_clr();
void lcd_csr(int r, int c);

#endif