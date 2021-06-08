#ifndef __LIB2_H__
#define __LIB2_H__
#include <stdint.h>
extern void _write(char * string, int color);
extern void _getBuffer(char * buffer, int bytes);
void printf(char *str, ...); 
void putChar(const char ascii);
char getChar();
int strlen(const char * string);
void strcpy(char *destination, const char *source);
int numToStr(int value, char *buffer, int base);
char *reverse(char *buffer, int i, int j);
void swap(char *x, char *y);
int strcmp(char * s1, char *s2);
int strToInt(char *str);
uint32_t * hexaStrToDir(char * hexaStr);
int pow(int base, int e);
void doubleToString(long double result, char * root);
int readNumFromLine(char * dest);
void stringToDouble(char * string, long double * num);
int strcpyTilPoint(char *destination, const char *source);
void printUser(char * name);
void printError(char * err);
#endif