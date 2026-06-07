#include "audio_manager.h"
#include "r2s.h"
#include "jl_uart.h"
#include "ft003.h"
#define R2S_GAIN 5
uint8_t getVol(uint8_t vol);

void audio_task_init() {
  initR2s();
  ft003_init();
}

static uint8_t current_master_vol = 0;

void fade_in_volume() {
  bool is_mute = (current_menu == MUTE_MENU || current_menu == STANDBY_MENU);
  static bool was_mute = true;
  static bool fading = false;
  static uint32_t timer = 0;

  if (!fading && !is_mute) {
      if (current_master_vol != audio.volume[MASTER]) {
          current_master_vol = audio.volume[MASTER];
          update_audio = true;
      }
  }

  // Detect UNMUTE edge
  if (was_mute && !is_mute) {
    current_master_vol = 0;
    timer = millis();
    fading = true;
  }

  // Handle fade process
  if (fading) {
    if (millis() - timer >= 50) {
      timer = millis();
      current_master_vol++;
      update_audio = true;
      if (current_master_vol >= audio.volume[MASTER]) {
        current_master_vol = audio.volume[MASTER];
        fading = false;
      }
    }
  }
  was_mute = is_mute;
}

void audio_task() {
  fade_in_volume();
  if (update_audio) {
    update_audio = false;
    static uint8_t last_input = 255;

    if (audio.input != last_input) {
      ft003_setMode(audio.input);
        last_input = audio.input;
        if (audio.input == USB_IN) {
            jl_send_cmd("USB\n");
        } else if (audio.input == BT_IN) {
            jl_send_cmd("BLE\n");
        } else if (audio.input == FM_IN) {
            jl_send_cmd("FM\n");
        } else {
            jl_send_cmd("STB\n");
        }
    }
    
    int in_slot = 0;
    int r_l_in = 0;

    if(audio.prologic_mode == 1){
      r_l_in = 1;
    }
    else{
    if (audio.input == USB_IN || audio.input == BT_IN || audio.input == FM_IN) {
        in_slot = 0;
        r_l_in = 0;
    } else if (audio.input == AUX_IN) {
        in_slot = 1;
        r_l_in = 0;
    } else if (audio.input == IN_5_1 || audio.input == ARC_IN || audio.input == OPT_IN || audio.input == COAX_IN) {
        in_slot = 0; // Don't care
        r_l_in = 1;
    }
  }



    // writeToAudioSlot1(in, out_gain, att, R_L_in, bass, treb, in_gain, toneEnable)
    writeToAudioSlot1(in_slot, audio.gain, 0, r_l_in, 15 - audio.volume[BASS], 15 - audio.volume[TREB], 0, 1);

    // Slot 2: Front
    writeToAudioSlot2(R2S_GAIN, getVol(audio.volume[FRONT]), R2S_GAIN, getVol(audio.volume[FRONT]));

    // Slot 3: Center & Sub
    // In Prologic Mode 1 & 2, we output to Center. If input is 5.1, we definitely output.
    // We'll just map the volumes directly for now as both modes activate the channels.
    writeToAudioSlot3(R2S_GAIN, getVol(audio.volume[CENTER]), R2S_GAIN, getVol(audio.volume[SUB]));

    // Slot 4: Rear
    // In Prologic modes, Rear is active.
    writeToAudioSlot4(R2S_GAIN, getVol(audio.volume[REAR]), R2S_GAIN, getVol(audio.volume[REAR]));
    DEBUG_PRINTF("R2S updated:\n In:%d, R_L_in:%d, Master:%d, Front:%d, Rear:%d, Center:%d, Sub:%d, Bass:%d, Treb:%d, Prologic:%d\n", audio.input, r_l_in, audio.volume[MASTER], audio.volume[FRONT], audio.volume[REAR], audio.volume[CENTER], audio.volume[SUB], audio.volume[BASS], audio.volume[TREB], audio.prologic_mode);
  }
}

uint8_t curve[101]={
  0,
  12,14,16,18,20,//1-5
  22,26,28,30,32,//5-10
  34,36,38,40,42,//10-15
  44,46,48,50,52,//15-20
  53,54,56,57,59,//20-25
  60,62,63,65,67,//25-30
  68,70,71,73,75,//30-35
  76,77,79,80,82,//35-40
  83,85,87,89,90,//40-45
  92,94,96,98,99 //45-49
  // 50 is mapped below
};

uint8_t getVol(uint8_t vol) {
  // vol is 0-50, master is 0-50
  uint8_t master = current_master_vol * 2;  // 0–100
  uint8_t v = vol * 2;                        // 0-100
  uint16_t temp = (uint16_t)v * master;       // prevent overflow
  uint8_t ch_vol = temp / 100;                // 0-100

  if (ch_vol > 100) ch_vol = 100;
  
  uint8_t atten = 99;
  if (ch_vol == 100) atten = 100; // mapped to max if needed, but curve max is 99
  else atten = curve[ch_vol];

  bool is_mute = (current_menu == MUTE_MENU || current_menu == STANDBY_MENU);
  uint8_t effV = is_mute ? 99 : 99 - atten;
  
  // ensure it doesn't drop below 0 if atten > 99
  if (!is_mute && atten > 99) effV = 0; 
  DEBUG_PRINTF("Eff Ch vol: %d\n",effV);
  return effV;
}