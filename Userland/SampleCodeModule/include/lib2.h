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
int numToStr(int value, char *buffer, int base);
char *reverse(char *buffer, int i, int j);
void swap(char *x, char *y);
int strcmp(char * s1, char *s2);
int strToInt(char *str, int* size);
uint32_t * hexaStrToDir(char * hexaStr);
int pow(int base, int e);
#endif