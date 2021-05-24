#ifndef __SYSHANDLER_H__
#define __SYSHANDLER_H__
#include <stdint.h>
#include <naiveConsole.h>
#include <keyboard.h>

extern int _RTC(int num);
extern void _getRegisters(uint64_t * regs);
void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2);
void read(unsigned char * r1, unsigned int r2);
void getTime(int* r1,int * r2);
void getReg(uint64_t * r1);
void getMem(uint32_t * dir, uint32_t * vec);

#endif