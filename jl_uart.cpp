#include "jl_uart.h"
#include "global.h"
#include "debug.h"

HardwareSerial jl_serial(PA10, PA9);

bool jl_is_playing = true;
char jl_song_name[17] = {0};
char jl_song_ext[8] = {0};
uint32_t jl_song_display_timer = 0;
bool jl_show_song = false;

bool jl_bt_connected = false;
char jl_bt_device_name[32] = {0};
bool jl_show_bt_status = false;
uint32_t jl_bt_status_timer = 0;

char jl_fm_freq[8] = "87.5";

static uint32_t last_cmd_time = 0;

void jl_uart_init() {
    jl_serial.begin(115200);
}

void jl_send_cmd(const char* cmd) {
    // Wait at least 50ms since the last command
    while (millis() - last_cmd_time < 50) {
        delay(1);
    }
    jl_serial.print(cmd);
    last_cmd_time = millis();
    DEBUG_PRINTF("JL Sent: %s\n", cmd);
}

void jl_uart_task() {
    static char buf[128];
    static uint8_t idx = 0;

    while (jl_serial.available()) {
        char c = jl_serial.read();
        if (c == '\n' || c == '\r') {
            if (idx > 0) {
                buf[idx] = '\0';
                
                // Parse the command
                if (strncmp(buf, "SONG:", 5) == 0) {
                    // It's a song name
                    char* songStr = buf + 5;
                    
                    // Separate extension if it exists
                    char* extPtr = strrchr(songStr, '.');
                    if (extPtr != NULL) {
                        *extPtr = '\0'; // terminate name
                        extPtr++; // move to extension
                        strncpy(jl_song_ext, extPtr, sizeof(jl_song_ext) - 1);
                        jl_song_ext[sizeof(jl_song_ext) - 1] = '\0';
                        // Convert to upper case for clean display
                        for(int i = 0; jl_song_ext[i]; i++){
                            jl_song_ext[i] = toupper(jl_song_ext[i]);
                        }
                    } else {
                        jl_song_ext[0] = '\0';
                    }
                    
                    strncpy(jl_song_name, songStr, 16);
                    jl_song_name[16] = '\0';
                    
                    // Trigger UI to show song asynchronously
                    jl_show_song = true;
                    jl_song_display_timer = millis();
                    update_ui = 1;
                } else if (strncmp(buf, "BT_CONN:", 8) == 0) {
                    strncpy(jl_bt_device_name, buf + 8, sizeof(jl_bt_device_name) - 1);
                    jl_bt_device_name[sizeof(jl_bt_device_name) - 1] = '\0';
                    char* newline = strpbrk(jl_bt_device_name, "\r\n");
                    if (newline) *newline = '\0';
                    
                    jl_bt_connected = true;
                    jl_show_bt_status = true;
                    jl_bt_status_timer = millis();
                    update_ui = 1;
                } else if (strncmp(buf, "BT_DISCON", 9) == 0) {
                    jl_bt_connected = false;
                    jl_show_bt_status = true;
                    jl_bt_status_timer = millis();
                    update_ui = 1;
                } else if (strncmp(buf, "FM_FREQ:", 8) == 0) {
                    strncpy(jl_fm_freq, buf + 8, sizeof(jl_fm_freq) - 1);
                    jl_fm_freq[sizeof(jl_fm_freq) - 1] = '\0';
                    char* newline = strpbrk(jl_fm_freq, "\r\n");
                    if (newline) *newline = '\0';
                    update_ui = 1;
                } else if (strncmp(buf, "MODE:", 5) == 0) {
                    char* modeStr = buf + 5;
                    char* newline = strpbrk(modeStr, "\r\n");
                    if (newline) *newline = '\0';

                    if (strcmp(modeStr, "USB") == 0) {
                        audio.input = USB_IN;
                    } else if (strcmp(modeStr, "BT") == 0) {
                        audio.input = BT_IN;
                    } else if (strcmp(modeStr, "FM") == 0) {
                        audio.input = FM_IN;
                    } else if (strcmp(modeStr, "LINE") == 0 || strcmp(modeStr, "AUX") == 0) {
                        audio.input = AUX_IN;
                    }
                    
                    update_ep = EP_INPUT;
                    update_audio = 1;
                    update_ui = 1;
                } else if (strstr(buf, "Uart 1 test data") != NULL) {
                    DEBUG_PRINTF("JL Chip UART Ready\n");
                }
                
                idx = 0;
            }
        } else {
            if (idx < sizeof(buf) - 1) {
                buf[idx++] = c;
            }
        }
    }
}
