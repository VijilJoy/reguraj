#include "controllers.h"

void control_forward(){
	update_ui=1;
	update_ep=1;
	if(current_menu == HOME_MENU){
	if(control_menu == MASTER){
		if(audio.volume[MASTER] < 50)
			audio.volume[MASTER]++;
			update_audio = 1;
	}
	if(control_menu == FRONT){
		if(audio.volume[FRONT] < 50)
			audio.volume[FRONT]++;
		update_audio = 1;
	}
	if(control_menu == REAR){
		if(audio.volume[REAR] < 50)
			audio.volume[REAR]++;
		update_audio = 1;
	}
	if(control_menu == CENTER){
		if(audio.volume[CENTER] < 50)
			audio.volume[CENTER]++;
		update_audio = 1;
	}
	if(control_menu == SUB){
		if(audio.volume[SUB] < 50)
			audio.volume[SUB]++;
		update_audio = 1;
	}
	if(control_menu == BASS){
		if(audio.volume[BASS] < 15)
			audio.volume[BASS]++;
		update_audio = 1;
	}
	if(control_menu == TREB){
		if(audio.volume[TREB] < 15)
			audio.volume[TREB]++;
		update_audio = 1;
	}
}
	if(control_menu == GAIN){
		if(audio.gain < 7)
			audio.gain++;
		update_audio = 1;
	}
	
}

void control_backward(){
	update_ui=1;
	update_ep=1;
	if(current_menu == HOME_MENU){
	if(control_menu == MASTER){
		if(audio.volume[MASTER] > 0)
			audio.volume[MASTER]--;
		update_audio = 1;
	}
	if(control_menu == FRONT){
		if(audio.volume[FRONT] > 0)
			audio.volume[FRONT]--;
		update_audio = 1;
	}
	if(control_menu == REAR){
		if(audio.volume[REAR] > 0)
			audio.volume[REAR]--;
		update_audio = 1;
	}
	if(control_menu == CENTER){
		if(audio.volume[CENTER] > 0)
			audio.volume[CENTER]--;
		update_audio = 1;
	}
	if(control_menu == SUB){
		if(audio.volume[SUB] > 0)
			audio.volume[SUB]--;
		update_audio = 1;
	}
	if(control_menu == BASS){
		if(audio.volume[BASS] > 0)
			audio.volume[BASS]--;
		update_audio = 1;
	}

	if(control_menu == TREB){
		if(audio.volume[TREB] > 0)
			audio.volume[TREB]--;
		update_audio = 1;
	}
}
	if(control_menu == GAIN){
		if(audio.gain > 0)
			audio.gain--;
		update_audio = 1;
	}

}
