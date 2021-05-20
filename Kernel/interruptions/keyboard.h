#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

extern char _getKey(); 
void keyboard_handler();
char getAscii(unsigned int key);
void removeBuffer();
char * getBuffer();
unsigned int getBufferSize();

#endif
