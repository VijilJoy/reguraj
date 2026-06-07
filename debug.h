#include "HardwareSerial.h"
#ifndef DEBUG_H
#define DEBUG_H
#define DEBUG_MODE 1
#if DEBUG_MODE
extern HardwareSerial debug;
#define DEBUG_INIT() debug.begin(115200)
#define DEBUG_PRINTF debug.printf
#define DEBUG_PRINT debug.print
#define DEBUG_PRINTLN debug.println
#else
#define DEBUG_INIT(...)
#define DEBUG_PRINTF(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif
#endif