#include "encoder.h"
#include <Arduino.h>

volatile bool enc_a, enc_b, enc_x, enc_y;
bool enc_s = 1;
unsigned long int sw_timer=0;
bool long_pressed=0;

void enc_switch(){
		last_ui_interaction = millis();
		control_menu++;
		if(control_menu>=GAIN)
			control_menu = MASTER;
}

void PinInterrupt_ISR()
{
	bool current_a = digitalRead(ENC_A);
	bool current_b = digitalRead(ENC_B);
	
	if(enc_a != current_a){
		enc_a = current_a;
		if((current_a == HIGH && current_b == LOW)){
			enc_x = 1;
			enc_y = 0;
		}
	}
	if(enc_b != current_b){
		enc_b = current_b;
		if(current_a == LOW && current_b == HIGH){
			enc_x = 0;
			enc_y = 1;
		}
	}
}

void encoder_init(void) {
	pinMode(ENC_A, INPUT_PULLUP);
	pinMode(ENC_B, INPUT_PULLUP);
	pinMode(ENC_S, INPUT_PULLUP);
	
	enc_a = digitalRead(ENC_A);
	enc_b = digitalRead(ENC_B);
	
	attachInterrupt(digitalPinToInterrupt(ENC_A), PinInterrupt_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENC_B), PinInterrupt_ISR, CHANGE);
}

void enc_task(void) {
		if(enc_x==0 && enc_y==1) {
			last_ui_interaction = millis();
			control_forward();
		}
		if(enc_x==1 && enc_y==0) {
			last_ui_interaction = millis();
			control_backward();
		}
		enc_x=enc_y=0;
		
		bool current_s = digitalRead(ENC_S);
		if(current_s==0){
			if(millis()-sw_timer>1000){
				if(long_pressed==0){
					long_pressed=1;
					last_ui_interaction = millis();
					audio.input++;
					if(audio.input>=IN_MAX)
						audio.input=USB_IN;
					update_audio = 1;
					update_ui=1;
					update_ep=EP_INPUT;
				}
			}
		}
		else{
			sw_timer=millis();
		}
		
		if(current_s!=enc_s){
			enc_s = current_s;
			update_ui=1;
			sw_timer = millis();
			if(long_pressed)long_pressed=0;
			else{
				if(current_s==1){
					enc_switch();
					delay(300);
				}
			}
		}
}
