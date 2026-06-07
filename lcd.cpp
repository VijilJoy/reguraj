#include "lcd.h"
#define LCD_LED PA8

void lcd_print(const char *str) {
  lcd.print(str);
}
void lcd_print(const unsigned char *str) {
  lcd.print((const char *)str);
}

void lcd_data(unsigned char dt, int r) {
  if (r) lcd.write(dt);
  else lcd.command(dt);
}

void lcd_crt_chr(unsigned char loc, const unsigned char *msg) {
  lcd.createChar(loc, (uint8_t *)msg);
}

void lcd_backlight(bool on) {
  digitalWrite(LCD_LED, on);
}
void lcd_init() {
  lcd.begin(16, 2);
  pinMode(LCD_LED, OUTPUT);
  lcd_backlight(1);
}
void lcd_clr() {
  lcd.clear();
}

void lcd_csr(int r, int c) {
  lcd.setCursor(r, c);
}
