#include "ui_manager.h"
#include "jl_uart.h"
#include <string.h>

bool started_up = 1;
uint32_t stb_timer = 0;
unsigned long int backlight_timer = 0;
bool timer_overflow = 0;
bool pow_led_state = LOW;
uint32_t last_ui_interaction = 0;
bool bt_blink_state = true;

void ui_init(){
	digitalWrite(pow_led, HIGH);
	delay(500);
	lcd_init();
	lcd_clr();
	lcd_backlight(1);
	
	lcd_csr(0,0);
	int spaces = (16 - strlen(brand_name)) / 2;
	for (int i=0; i<spaces; i++) lcd_print(" ");
	lcd_print(brand_name);
	
	create_big_num();
	delay(5000);
	lcd_clr();
	digitalWrite(pow_led, LOW);
}

void ui_task(){
	static int last_format = -1;
	static int pending_format = -1;
	static uint32_t format_change_timer = 0;

	int pcm = digitalRead(PCM_PIN);
	int dolby = digitalRead(DBY_PIN);
	int dts = digitalRead(DTS_PIN);
	int current_format = (pcm << 2) | (dolby << 1) | dts;
	
	if (current_format != pending_format) {
		pending_format = current_format;
		format_change_timer = millis();
	}

	if ((millis() - format_change_timer > 300) && (current_format != last_format)) {
		last_format = current_format;
		update_ui = 1;
	}

	if (jl_show_song) {
		if (millis() - jl_song_display_timer > 2000) {
			jl_show_song = false;
			update_ui = 1;
			clr_display = 1;
		}
	}

	if (jl_show_bt_status) {
		if (millis() - jl_bt_status_timer > 2000) {
			jl_show_bt_status = false;
			update_ui = 1;
			clr_display = 1;
		}
	}

	static uint32_t bt_blink_timer = 0;
	if (audio.input == BT_IN && !jl_bt_connected && current_menu == HOME_MENU && !jl_show_song && !jl_show_bt_status && display_timer_enable) {
		if (millis() - bt_blink_timer >= 500) {
			bt_blink_timer = millis();
			bt_blink_state = !bt_blink_state;
			lcd_csr(0,0);
			if (bt_blink_state) {
				lcd_print("<BLE:IN>");
			} else {
				lcd_print("        ");
			}
		}
	} else if (audio.input == BT_IN && jl_bt_connected && !bt_blink_state) {
		bt_blink_state = true;
		update_ui = 1;
	}

	if(display_timer_enable && current_menu == HOME_MENU){
		if (control_menu == MASTER) {
			static bool reverted_to_format = false;
			if (millis() - last_ui_interaction > 2000 && !reverted_to_format) {
				reverted_to_format = true;
				update_ui = 1;
			} else if (millis() - last_ui_interaction <= 2000) {
				reverted_to_format = false;
			}
		}
	}

	if(clr_display){
		clr_display=0;
		lcd_clr();
	}
	if(display_timer_enable){
		if(millis()-backlight_timer > (started_up?7000:3000)){
			if(timer_overflow){
				timer_overflow=0;
			started_up=0;
			lcd_backlight(0);
			digitalWrite(pow_led, HIGH);
			control_menu=MASTER;
			display_home_menu(); 
			}
		}
		else{
			timer_overflow=1;
		}
	}
	else{
		lcd_backlight(1);
		digitalWrite(pow_led, LOW);
	}
	if(display_msg.line1[0]!=0 || display_msg.line2[0]!=0){
		lcd_clr();
		backlight_timer=millis();
		lcd_backlight(1);
		digitalWrite(pow_led, LOW);
		delay(10);
		lcd_csr(display_msg.c1,0);
		lcd_print(display_msg.line1);
		lcd_csr(display_msg.c2,1);
		lcd_print(display_msg.line2);
		delay(2000);
		lcd_clr();
		display_msg.c1 = 0;
		display_msg.c2 = 0;
		display_msg.line1="";
		display_msg.line2="";
	}
	if(update_ui){
		update_ui = 0;
		backlight_timer=millis();
		lcd_backlight(1);
		digitalWrite(pow_led, LOW);
		switch(current_menu){
			case HOME_MENU: 
				display_timer_enable=1;
				display_home_menu(); 
			break;
			case GAIN_MENU:
				show_gain_menu();
				break;
			case PAYMENT_LOCK_MENU:
				break;
			case STANDBY_MENU:
				display_timer_enable=0;
				show_stb_mode();
				break;
			case MUTE_MENU:
				display_timer_enable=0;
				lcd_clr();
				print_mute();
				break;
			case NAME_EDITOR_MENU:
				display_timer_enable=0;
				show_name_editor();
				break;
			default:
				current_menu=HOME_MENU;
				update_ui=0;
		};
	}
	if(current_menu==STANDBY_MENU){
		if(millis()-stb_timer>1000){
		stb_timer=millis();
		pow_led_state = !pow_led_state;
		digitalWrite(pow_led, pow_led_state);
	}
	}
	
}

void show_stb_mode(){
	lcd_clr();
	delay(10);
	lcd_csr(4,0);
	lcd_print("STAND-BY");
	lcd_csr(0,1);
	int spaces = (16 - strlen(brand_name)) / 2;
	for (int i=0; i<spaces; i++) lcd_print(" ");
	lcd_print(brand_name);
}

void show_name_editor(){
	lcd_clr();
	delay(10);
	lcd_csr(0,0);
	lcd_print(brand_name);
	lcd.setCursor(name_cursor_pos, 0);
	lcd.blink();
}

void show_gain_menu(){
	char str[8]="GAIN: ";
	lcd_csr(0,0);
	str[6]=audio.gain/10 + 48;
	str[7]=audio.gain%10 + 48;
	lcd_print(str);
}

void display_home_menu(){
	if (jl_show_bt_status) {
		lcd_csr(0,0);
		if (jl_bt_connected) {
			lcd_print("BT Connected    ");
			lcd_csr(0,1);
			lcd_print(jl_bt_device_name);
			for(int i=strlen(jl_bt_device_name); i<16; i++) lcd_print(" ");
		} else {
			lcd_print("BT Disconnected ");
			lcd_csr(0,1);
			lcd_print("                ");
		}
		return;
	}

	if (jl_show_song) {
		lcd_csr(0,0);
		lcd_print(jl_song_name);
		for(int i=strlen(jl_song_name); i<16; i++) lcd_print(" ");
		
		lcd_csr(0,1);
		lcd_print(jl_song_ext);
		for(int i=strlen(jl_song_ext); i<16; i++) lcd_print(" ");
		return;
	}

	const char* input_text ="<USB:IN>";
	const char* control_text ="<MASTER>";
	char value=audio.volume[MASTER];
	
	switch(audio.input){
		case BT_IN: input_text = bt_blink_state ? "<BLE:IN>" : "        "; break;
		case FM_IN: input_text="< FM:IN>"; break;
		case AUX_IN: input_text="<AUX:IN>"; break;
		case IN_5_1: input_text="<5.1:IN>"; break;
		case ARC_IN: input_text="<ARC:IN>"; break;
		case OPT_IN: input_text="<OPT:IN>"; break;
		case COAX_IN: input_text="<COX:IN>"; break;
	};
	
	switch(control_menu){
		case MASTER:
			if (millis() - last_ui_interaction > 2000) {
				int pcm = digitalRead(PCM_PIN);
				int dolby = digitalRead(DBY_PIN);
				int dts = digitalRead(DTS_PIN);
				if (pcm + dolby + dts == 1) {
					if (pcm) control_text = "< PCM  >";
					else if (dolby) control_text = "<DOLBY >";
					else if (dts) control_text = "< DTS  >";
				} else if (audio.input == FM_IN) {
					static char fm_buf[16];
					snprintf(fm_buf, sizeof(fm_buf), "<%5s >", jl_fm_freq);
					control_text = fm_buf;
				}
			}
			break;
		case FRONT: control_text="<FRONT >"; value=audio.volume[FRONT]; break;
		case REAR: control_text="< RAER >"; value=audio.volume[REAR]; break;
		case CENTER: control_text="<CENTER>"; value=audio.volume[CENTER]; break;
		case SUB: control_text="< SUB  >"; value=audio.volume[SUB]; break;
		case BASS: control_text="< BASS >"; value=audio.volume[BASS]; break;
		case TREB: control_text="< TREB >"; value=audio.volume[TREB]; break;
	};
	
	lcd_csr(0,0);
	lcd_print(input_text);
	lcd_csr(0,1);
	lcd_print(control_text);
	
	display_value(value);
}

void display_value(char num){
	print_big_num(num/10,9);
	print_big_num(num%10,12);
}

void print_big_num(char n,char x){
switch (n)
  {
    case 0:
    {
      
			lcd_csr(x,0);
      lcd_data(0,1);
      lcd_data(1,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data(0,1);
      lcd_data(4,1);
      lcd_data(2,1);
      break;
    }
    case 1:
    {
      lcd_csr(x,0);
      lcd_data((char)254,1);
      lcd_data((char)254,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data((char)254,1);
      lcd_data((char)254,1);
      lcd_data(2,1);
      break;
    }
    case 2:
    {
      lcd_csr(x,0);
      lcd_data(3,1);
      lcd_data(6,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data(0,1);
      lcd_data(4,1);
      lcd_data(4,1);
      break;
    }
    case 3:
    {
      lcd_csr(x,0);
      lcd_data(3,1);
      lcd_data(6,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data(7,1);
      lcd_data(4,1);
      lcd_data(2,1);
      break;
    }
    case 4:
    {
      lcd_csr(x,0);
      lcd_data(0,1);
      lcd_data(4,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data((char)254,1);
      lcd_data((char)254,1);
      lcd_data(2,1);
      break;
    }
    case 5:
    {
      lcd_csr(x,0);
      lcd_data(0,1);
      lcd_data(6,1);
      lcd_data(5,1);
      lcd_csr(x,1);
      lcd_data(7,1);
      lcd_data(4,1);
      lcd_data(2,1);
      break;
    }
    case 6:
    {
      lcd_csr(x,0);
      lcd_data(0,1);
      lcd_data(6,1);
      lcd_data(5,1);
      lcd_csr(x,1);
      lcd_data(0,1);
      lcd_data(4,1);
      lcd_data(2,1);
      break;
    }
    case 7:
    {
      lcd_csr(x,0);
      lcd_data(1,1);
      lcd_data(1,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data((char)254,1);
      lcd_data((char)254,1);
      lcd_data(2,1);
      break;
    }
    case 8:
    {
      lcd_csr(x,0);
      lcd_data(0,1);
      lcd_data(6,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data(0,1);
      lcd_data(4,1);
      lcd_data(2,1);
      break;
    }
    case 9:
    {
      lcd_csr(x,0);
      lcd_data(0,1);
      lcd_data(6,1);
      lcd_data(2,1);
      lcd_csr(x,1);
      lcd_data(7,1);
      lcd_data(4,1);
      lcd_data(2,1);
      break;
    }
  }
}

void print_mute()
{
	lcd_clr();
	lcd_csr(6,0);
	lcd_print("MUTE");
}
