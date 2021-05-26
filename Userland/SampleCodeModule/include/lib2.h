#ifndef __LIB2_H__
#define __LIB2_H__
#include <stdint.h>
extern void _write(char * string);
extern void _getBuffer(char * buffer, int bytes);
int scanf();
void printf(char *str, ...); 
void putChar(const char ascii);
char getChar();
int strlen(const char * string);
char *strcpy(char *destination, const char *source);
char *numToStr(int value, char *buffer, int base);
char *reverse(char *buffer, int i, int j);
void swap(char *x, char *y);
#endif