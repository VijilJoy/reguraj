#ifndef EPROM_H
#define EPROM_H

#include "global.h"

void eprom_w(char add, char dat);
char eprom_r(char add);
void eprom_load();
void eprom_task();
void eprom_save_name();

#define EP_NAME_START 16

#endif
