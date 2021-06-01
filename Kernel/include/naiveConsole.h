#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>
void changeScreen(int screen);
void ncPrint(const char * string, int fd);
void ncPrintChar(char character, int color);
void ncNewline();
void ncClear();
void scroll();
void drawLine();
void clearLine(uint8_t * p);
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void intToHexaStr(char * buff);
#endif