#ifndef JL_UART_H
#define JL_UART_H

#include <Arduino.h>

extern bool jl_is_playing;
extern char jl_song_name[17];
extern char jl_song_ext[8];
extern uint32_t jl_song_display_timer;
extern bool jl_show_song;

extern bool jl_bt_connected;
extern char jl_bt_device_name[32];
extern bool jl_show_bt_status;
extern uint32_t jl_bt_status_timer;

extern char jl_fm_freq[8];

void jl_uart_init();
void jl_uart_task();
void jl_send_cmd(const char* cmd);

#endif
