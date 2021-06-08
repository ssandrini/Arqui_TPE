#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <videoDriver.h>

void changeScreen(int screen);
void ncPrint(const char * string, int fd);
void ncNewLine();
void ncClear(int currentScreen);
void scroll();
void middleLine();
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void intToHexaStr(char * buff);
#endif