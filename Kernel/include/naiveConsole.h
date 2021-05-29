#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>
void changeScreen(int screen);
void ncPrint(const char * string, int fd);
void ncPrintChar(char character, int color);
void ncNewline();
void ncClear();
void scroll();
void clearLine(uint8_t * p);
#endif