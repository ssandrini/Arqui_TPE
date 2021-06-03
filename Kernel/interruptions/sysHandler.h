#ifndef __SYSHANDLER_H__
#define __SYSHANDLER_H__
#include <stdint.h>
#include <naiveConsole.h>
#include <keyboard.h>

extern int _RTC(int num);
extern void _getRegisters(uint64_t * regs);
extern void _cpuid(uint32_t * r1,uint32_t * r2, int * id);
extern int _cpuidSupport();
void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t rsp) ;
void read(unsigned char * r1, unsigned int r2);
void getTimeRTC(uint64_t r1, uint64_t r2);
void getReg(uint64_t * r1, uint64_t * stackFrame);
void getMem(uint32_t * dir, uint32_t * vec);
void clearScreen(int currentScreen);
void getInfo(uint32_t * r1, uint32_t * r2, int * id);

#endif