#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#include "app_main.h"
#include "lcd.h"
#include "ui_manager.h"
#include "encoder.h"
#include "eprom.h"
#include "nec_ir.h"
#include "audio_manager.h"
#include "jl_uart.h"
#include "string.h"
#include "global.h"
LiquidCrystal lcd(PA12, PA11, PB15, PB14, PB13, PB12);
#if DEBUG_MODE
HardwareSerial debug(PA3, PA2);
#endif

void app_main() {
	DEBUG_INIT();
	DEBUG_PRINTF("App starting. Build: " __DATE__
	             "," __TIME__
	             "");
	// pinMode(pow_led, OUTPUT);
	// pinMode(usb_en, OUTPUT);
	// digitalWrite(pow_led, LOW);
	// digitalWrite(usb_en, LOW);

	// i2c_init();

	lcd.begin(16, 2);
	lcd.clear();
	delay(10);
	Wire.begin();
	eprom_load();
	ui_init();
	encoder_init();
	
	IR_RemoteInit();
	jl_uart_init();
	audio_task_init();

	pinMode(PCM_PIN, INPUT);
	pinMode(DBY_PIN, INPUT);
	pinMode(DTS_PIN, INPUT);


	while (1) {
		ir_task();
		ui_task();
		enc_task();
		eprom_task();
		audio_task();
		usb_en_task();
		jl_uart_task();
	}
}
