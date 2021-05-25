#ifndef __LIB2_H__
#define __LIB2_H__
extern void _write(char * string);
extern void _getBuffer(char * buffer, int bytes);
int scanf();
void printf(char* format,...); 
void putChar(const char ascii);
char getChar();
int intToBase(int value, char * buffer, unsigned int base);
#endif