#include "global.h"

char h_code[4]="000";
char h_code_index=0;

char brand_name[17] = "Q-Tech AUDIOS   ";
uint8_t name_cursor_pos = 0;

bool update_ui = 1;
bool display_timer_enable = 0;
bool clr_display = 1;

struct Dispaly_msg display_msg={"","",0};

uint8_t update_ep = 0;
uint8_t update_audio = 1;
uint8_t current_menu = 0;
uint8_t control_menu = 0;

struct Aduio audio;

void append_code(char val){
	h_code[h_code_index]=val;
	h_code_index++;
	if(h_code_index>3)
		h_code_index=0;
}

void usb_en_task(){
	if(audio.input == USB_IN){
		digitalWrite(usb_en, HIGH);
	}
	else{
		digitalWrite(usb_en, LOW);
	}
}
