#include "eprom.h"
#include <Wire.h>
#include "lcd.h"

#define DEV_ADD 0x50

void eprom_w(char add, char dat) {
    Wire.beginTransmission(DEV_ADD);
    Wire.write(add);
    Wire.write(dat);
    Wire.endTransmission();
    delay(5);
}

char eprom_r(char add) {
    char rdata = 0xFF;

    Wire.beginTransmission(DEV_ADD);
    Wire.write(add);
    Wire.endTransmission();

    Wire.requestFrom((uint8_t)DEV_ADD, (uint8_t)1);
    if (Wire.available()) {
        rdata = Wire.read();
    }

    delay(50);

    return rdata;
}

void eprom_load(){
	if(eprom_r(EP_TEST)==0x45){
		audio.volume[MASTER]=eprom_r(EP_MASTER);
		audio.volume[FRONT]=eprom_r(EP_FRONT);
		audio.volume[REAR]=eprom_r(EP_REAR);
		audio.volume[CENTER]=eprom_r(EP_CEN);
		audio.volume[SUB]=eprom_r(EP_SUB);
		audio.volume[BASS]=eprom_r(EP_BASS);
		audio.volume[TREB]=eprom_r(EP_TREB);
		audio.input = eprom_r(EP_INPUT);
		audio.gain = eprom_r(EP_GAIN);
		audio.prologic_mode = eprom_r(EP_PROLOGIC);

		// Clamp values for safety
		if(audio.volume[MASTER] > 50) audio.volume[MASTER] = 25;
		if(audio.volume[FRONT] > 50) audio.volume[FRONT] = 25;
		if(audio.volume[REAR] > 50) audio.volume[REAR] = 25;
		if(audio.volume[CENTER] > 50) audio.volume[CENTER] = 25;
		if(audio.volume[SUB] > 50) audio.volume[SUB] = 25;
		
		if(audio.volume[BASS] > 15) audio.volume[BASS] = 7;
		if(audio.volume[TREB] > 15) audio.volume[TREB] = 7;
		
		if(audio.input >= IN_MAX) audio.input = 0;
		if(audio.gain > 7) audio.gain = 5;
		if(audio.prologic_mode < 1 || audio.prologic_mode > 2) audio.prologic_mode = 1;
	}
	else{
		eprom_w(EP_TEST,0x45);
		audio.volume[MASTER] = 25;
		audio.volume[FRONT] = 25;
		audio.volume[REAR] = 25;
		audio.volume[CENTER] = 25;
		audio.volume[SUB] = 25;
		audio.volume[BASS] = 7;
		audio.volume[TREB] = 7;
		audio.input = 0;
		audio.gain = 5;
		audio.prologic_mode = 1;
		
		// Write default name to EEPROM
		for (int i = 0; i < 16; i++) {
			eprom_w(EP_NAME_START + i, brand_name[i]);
		}
	}
	
	// Read name from EEPROM
	for (int i = 0; i < 16; i++) {
		char c = eprom_r(EP_NAME_START + i);
		if (c >= 32 && c <= 126) {
			brand_name[i] = c;
		} else {
			brand_name[i] = ' ';
		}
	}
	brand_name[16] = '\0';
	// else{
	// 	lcd_print("EEPROM ERROR!!");
	// 	eprom_w(EP_TEST,0x48);
	// 	delay(1000);
	// 	NVIC_SystemReset();
	// }
}

void eprom_task(){
	if(update_ep==1){
		update_ep=0;
		switch(control_menu){
			case MASTER: eprom_w(EP_MASTER,audio.volume[MASTER]); break;
			case FRONT: eprom_w(EP_FRONT,audio.volume[FRONT]); break;
			case REAR: eprom_w(EP_REAR,audio.volume[REAR]); break;
			case CENTER: eprom_w(EP_CEN,audio.volume[CENTER]); break;
			case SUB: eprom_w(EP_SUB,audio.volume[SUB]); break;
			case BASS: eprom_w(EP_BASS,audio.volume[BASS]); break;
			case TREB: eprom_w(EP_TREB,audio.volume[TREB]); break;
		}
	}
	else if(update_ep>1){
		switch(update_ep){
			case EP_INPUT: eprom_w(EP_INPUT,audio.input); break;
			case EP_GAIN: eprom_w(EP_GAIN,audio.gain); break;
			case EP_PROLOGIC: eprom_w(EP_PROLOGIC,audio.prologic_mode); break;
		}
	}
}

void eprom_save_name() {
	for (int i = 0; i < 16; i++) {
		eprom_w(EP_NAME_START + i, brand_name[i]);
		delay(15); // Extra delay to guarantee EEPROM write cycle completes
	}
}
