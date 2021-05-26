#ifndef __LIB2_H__
#define __LIB2_H__
extern void _write(char * string);
extern void _getBuffer(char * buffer, int bytes);
int scanf();
void printf(char* format,...); 
void putChar(const char ascii);
char getChar();
int strlen(const char * string);
//// SANTI /////////
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char* itoa(int value, char* buffer, int base);
///// FIN SANTI////////////
#endif