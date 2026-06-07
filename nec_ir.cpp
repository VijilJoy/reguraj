#include "nec_ir.h"
#include <IRremote.hpp>
#include "ui_manager.h"
#include "global.h"
#include "jl_uart.h"

void send_nec_raw(uint32_t cde) {
    uint8_t i;

    // Leader signal
    digitalWrite(IR_SEND_PIN, LOW);
    delayMicroseconds(9000);  // 9ms
    digitalWrite(IR_SEND_PIN, HIGH);
    delayMicroseconds(4500);   // 4.5ms

    // Send 32 bits LSB first
    for (i = 0; i < 32; i++) {
        digitalWrite(IR_SEND_PIN, LOW);
        delayMicroseconds(562);  // NEC pulse for each bit

        digitalWrite(IR_SEND_PIN, HIGH);
        if (cde & 0x01) {
            delayMicroseconds(1685);  // 1 for 1.685ms
        } else {
            delayMicroseconds(562);  // 0 for 562µs
        }
        cde >>= 1;
    }

    // Stop bit (562µs pulse)
    digitalWrite(IR_SEND_PIN, LOW);
    delayMicroseconds(562);
    digitalWrite(IR_SEND_PIN, HIGH);

    // Optional cooldown time
    delay(40);  // 40ms before next command
}


#include "eprom.h"
#include "lcd.h"

void handleKeyAction(uint16_t key) {
	DEBUG_PRINTF("IR Key: 0x%04X\n", key);
	
	if (current_menu == NAME_EDITOR_MENU) {
		static uint16_t last_t9_key = 0;
		static uint8_t t9_press_count = 0;
		static uint32_t last_t9_time = 0;

		const char* t9_chars[] = {
			" 0-",      // 0
			".,?!1",    // 1
			"ABCabc2",  // 2
			"DEFdef3",  // 3
			"GHIghi4",  // 4
			"JKLjkl5",  // 5
			"MNOmno6",  // 6
			"PQRSpqrs7",// 7
			"TUVtuv8",  // 8
			"WXYZwxyz9" // 9
		};

		int key_idx = -1;
		switch(key) {
			case ZERO: key_idx = 0; break;
			case ONE: key_idx = 1; break;
			case TWO: key_idx = 2; break;
			case THREE: key_idx = 3; break;
			case FOUR: key_idx = 4; break;
			case FIVE: key_idx = 5; break;
			case SIX: key_idx = 6; break;
			case SEVEN: key_idx = 7; break;
			case EIGHT: key_idx = 8; break;
			case NINE: key_idx = 9; break;
		}

		if (key_idx >= 0) {
			if (key == last_t9_key && (millis() - last_t9_time < 1500)) {
				t9_press_count++;
			} else {
				if (last_t9_key != 0 && (millis() - last_t9_time < 1500)) {
					if (name_cursor_pos < 15) name_cursor_pos++;
				}
				last_t9_key = key;
				t9_press_count = 0;
			}
			last_t9_time = millis();
			
			int len = 0;
			while(t9_chars[key_idx][len]) len++;
			
			brand_name[name_cursor_pos] = t9_chars[key_idx][t9_press_count % len];
			update_ui = 1;
			return;
		}

		if (key == CH_MINU) {
			if (name_cursor_pos > 0) name_cursor_pos--;
			last_t9_key = 0;
			update_ui = 1;
		} else if (key == CH_PLUS) {
			if (name_cursor_pos < 15) name_cursor_pos++;
			last_t9_key = 0;
			update_ui = 1;
		} else if (key == SLEEP_MIN) {
			brand_name[name_cursor_pos] = ' ';
			if (name_cursor_pos > 0) name_cursor_pos--;
			last_t9_key = 0;
			update_ui = 1;
		} else if (key == PLAY_PAUS) {
			brand_name[name_cursor_pos] = ' ';
			if (name_cursor_pos < 15) name_cursor_pos++;
			last_t9_key = 0;
			update_ui = 1;
		} else if (key == VOL_PLUS) {
			for (int i = 15; i > 0; i--) {
				brand_name[i] = brand_name[i-1];
			}
			brand_name[0] = ' ';
			if (name_cursor_pos < 15) name_cursor_pos++;
			last_t9_key = 0;
			update_ui = 1;
		} else if (key == VOL_MINU) {
			for (int i = 0; i < 15; i++) {
				brand_name[i] = brand_name[i+1];
			}
			brand_name[15] = ' ';
			if (name_cursor_pos > 0) name_cursor_pos--;
			last_t9_key = 0;
			update_ui = 1;
		} else if (key == SAVE_R) {
			eprom_save_name();
			current_menu = HOME_MENU;
			lcd.noBlink();
			update_ui = 1;
			last_t9_key = 0;
		}
		return;
	}

	switch (key) {
		case VOL_PLUS:
			send_nec_raw(IR_EMIT_VOL_PLUS);
			if (current_menu == HOME_MENU)
				control_menu = MASTER;
			if (current_menu == GAIN_MENU)
				control_menu = GAIN;
			control_forward();
			break;

		case VOL_MINU:
			send_nec_raw(IR_EMIT_VOL_MINUS);
			if (current_menu == HOME_MENU)
				control_menu = MASTER;
			if (current_menu == GAIN_MENU)
				control_menu = GAIN;
			control_backward();
			break;

		case SL_PLUS:
			control_menu = FRONT;
			control_forward();
			break;
		case SL_MINU:
			control_menu = FRONT;
			control_backward();
			break;

		case SR_PLUS:
			control_menu = REAR;
			control_forward();
			break;
		case SR_MINU:
			control_menu = REAR;
			control_backward();
			break;

		case CEN_PLUS:
			control_menu = CENTER;
			control_forward();
			break;

		case CEN_MINU:
			control_menu = CENTER;
			control_backward();
			break;

		case SW_PLUS:
			control_menu = SUB;
			control_forward();
			break;
		case SW_MINU:
			control_menu = SUB;
			control_backward();
			break;

		case FL_PLUS:
			control_menu = BASS;
			control_forward();
			break;
		case FL_MINU:
			control_menu = BASS;
			control_backward();
			break;

		case FR_PLUS:
			control_menu = TREB;
			control_forward();
			break;
		case FR_MINU:
			control_menu = TREB;
			control_backward();
			break;

		case CH_PLUS:
			send_nec_raw(IR_EMIT_FWD);
			if (audio.input == USB_IN || audio.input == BT_IN || audio.input == FM_IN) {
				jl_send_cmd("NXT\n");
				if (audio.input == FM_IN) last_ui_interaction -= 2000;
			}
			break;
		case CH_MINU:
			send_nec_raw(IR_EMIT_BACKW);
			if (audio.input == USB_IN || audio.input == BT_IN || audio.input == FM_IN) {
				jl_send_cmd("PRV\n");
				if (audio.input == FM_IN) last_ui_interaction -= 2000;
			}
			break;
		case PLAY_PAUS:
			send_nec_raw(IR_EMIT_PLAY_PAUSE);
			if (audio.input == USB_IN || audio.input == BT_IN || audio.input == FM_IN) {
				if (jl_is_playing) {
					jl_send_cmd("PAU\n");
					jl_is_playing = false;
				} else {
					jl_send_cmd("PLY\n");
					jl_is_playing = true;
				}
				if (audio.input == FM_IN) last_ui_interaction -= 2000;
			}
			break;


		case USB:
			send_nec_raw(IR_EMIT_MODE);
			audio.input = USB_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case AUTO:
			audio.input = BT_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case SD_FM:
			audio.input = FM_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case AUX:
			audio.input = AUX_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case DVD:
			audio.input = IN_5_1;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case EQ_M:
			send_nec_raw(IR_EMIT_EQ);
			audio.input = ARC_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case EQ_P:
			send_nec_raw(IR_EMIT_EQ);
			audio.input = OPT_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;
		case DIS_M:
			audio.input = COAX_IN;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_INPUT;
			break;

		case ZERO: send_nec_raw(IR_EMIT_0); append_code('0'); break;
		case ONE: send_nec_raw(IR_EMIT_1); append_code('1'); break;
		case TWO: send_nec_raw(IR_EMIT_2); append_code('2'); break;
		case THREE: send_nec_raw(IR_EMIT_3); append_code('3'); break;
		case FOUR: send_nec_raw(IR_EMIT_4); append_code('4'); break;
		case FIVE: send_nec_raw(IR_EMIT_5); append_code('5'); break;
		case SIX: send_nec_raw(IR_EMIT_6); append_code('6'); break;
		case SEVEN: send_nec_raw(IR_EMIT_7); append_code('7'); break;
		case EIGHT: send_nec_raw(IR_EMIT_8); append_code('8'); break;
		case NINE: send_nec_raw(IR_EMIT_9); append_code('9'); break;
		case RESET:
			if (h_code[0] == '1' && h_code[1] == '2' && h_code[2] == '3' && h_code[3] == '4') {
				display_msg.line1 = "Gain Setting";
				display_msg.c1 = 1;
				current_menu = GAIN_MENU;
				control_menu = GAIN;
				display_timer_enable = 0;
				update_ui = 1;
			} else {
				char c3 = h_code[(h_code_index + 3) % 4];
				char c2 = h_code[(h_code_index + 2) % 4];
				char c1 = h_code[(h_code_index + 1) % 4];
				if (c1 == '1' && c2 == '5' && c3 == '6') {
					lcd_clr();
					lcd_csr(2,0);
					lcd_print("Name Editor");
					delay(1000);
					
					current_menu = NAME_EDITOR_MENU;
					name_cursor_pos = 0;
					display_timer_enable = 0;
					update_ui = 1;
				}
			}
			h_code[0] = 0;
			h_code_index = 0;
			break;
		case SAVE_R:
			if (control_menu == GAIN) {
				display_msg.line1 = "Saving...";
				update_ep = EP_GAIN;
				current_menu = HOME_MENU;
				control_menu = MASTER;
				update_ui = 1;
			}
			break;
		case MUTE:
			send_nec_raw(IR_EMIT_MUTE);
			update_ui = 1;
			if (current_menu == STANDBY_MENU)
				break;

			if (current_menu != MUTE_MENU) {
				current_menu = MUTE_MENU;
				update_audio = 1;
			} else {
				current_menu = HOME_MENU;
				update_audio = 1;
				clr_display = 1;
			}
			break;
		case PRO:
			if (audio.prologic_mode == 1) {
				audio.prologic_mode = 2;
				display_msg.line1 = "PROLOGIC MODE 2";
			} else {
				audio.prologic_mode = 1;
				display_msg.line1 = "PROLOGIC MODE 1";
			}
			display_msg.c1 = 0;
			update_ui = 1;
			update_audio = 1;
			update_ep = EP_PROLOGIC;
			break;
		case POWER:
			update_ui = 1;
			update_audio = 1;
			if (current_menu != STANDBY_MENU) {
				current_menu = STANDBY_MENU;
				jl_send_cmd("STB\n");
			} else {
				current_menu = HOME_MENU;
				control_menu = MASTER;
				update_ui = 1;
				update_audio = 1;
				jl_send_cmd("POW\n");
				display_msg.line1 = brand_name;
				display_msg.line2 = "";
				display_msg.c1 = 0;
				display_msg.c2 = 0;
			}
			break;
		default:
			break;
	}
}

void ir_task(void) {
	static uint16_t lastKey = 0;
	static unsigned long pressStart = 0;
	static unsigned long lastAction = 0;
	static unsigned long lastReceive = 0;

	if (IrReceiver.decode()) {
		unsigned long now = millis();
		
		// Strictly accept only NEC protocol. This filters out all UNKNOWN noise.
		if (IrReceiver.decodedIRData.protocol == NEC) {
			uint8_t cmd = IrReceiver.decodedIRData.command;
			uint16_t key = ((~cmd & 0xFF) << 8) | cmd;

			if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
				// Real NEC repeats happen every ~110ms. 
				// If we haven't seen a signal for > 200ms, this is a fake/noise repeat.
				if ((now - lastReceive) > 200) {
					lastKey = 0;
				} else if (lastKey != 0) {
					lastReceive = now;
					if ((now - pressStart) > 500) {
						if ((now - lastAction) > 200) {
							lastAction = now;
							last_ui_interaction = millis();
							handleKeyAction(lastKey);
						}
					}
				}
			} else {
				lastKey = key;
				pressStart = now;
				lastAction = now;
				lastReceive = now;
				last_ui_interaction = millis();
				handleKeyAction(key);
			}
		}
		IrReceiver.resume();
	}
}

void IR_RemoteInit(void) {
	IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
	pinMode(IR_SEND_PIN, OUTPUT);
}
