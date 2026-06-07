#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include "debug.h"

#define pow_led PA0
#define usb_en PA1

#define PCM_PIN PB3
#define DBY_PIN PA14
#define DTS_PIN PA15

extern char h_code[4];
extern char h_code_index;

extern char brand_name[17];
extern uint8_t name_cursor_pos;

void append_code(char val);

enum Menu{
	HOME_MENU,
	GAIN_MENU,
	PAYMENT_LOCK_MENU,
	STANDBY_MENU,
	MUTE_MENU,
	NAME_EDITOR_MENU,
	MENU_MAX
};

enum Input{
	USB_IN,
	BT_IN,
	FM_IN,
	AUX_IN,
	IN_5_1,
	ARC_IN,
	OPT_IN,
	COAX_IN,
	IN_MAX
};

enum Controls{
	MASTER,
	FRONT,
	REAR,
	CENTER,
	SUB,
	BASS,
	TREB,
	GAIN,
	CONTROL_MENU_MAX
};

enum EP_SUB_ADRESS{
    EP_MASTER = 0,
    EP_FRONT,
    EP_REAR,
    EP_CEN,
    EP_SUB,
    EP_BASS,
    EP_TREB,
    EP_INPUT,
		EP_STB,
		EP_GAIN,
		EP_TEST,
		EP_PROLOGIC,
		EP_MAX
};


extern bool update_ui;
extern bool display_timer_enable;
extern bool clr_display;
extern uint32_t last_ui_interaction;

struct Dispaly_msg{
	const char *line1;
	const char *line2;
	uint8_t c1,c2;
};
extern struct Dispaly_msg display_msg;

extern uint8_t update_ep;
extern uint8_t update_audio;
extern uint8_t current_menu;
extern uint8_t control_menu;

struct Aduio{
	uint8_t volume[CONTROL_MENU_MAX ];
	uint8_t input;
	uint8_t gain;
	uint8_t prologic_mode;
};
extern struct Aduio audio;

void usb_en_task();

#endif