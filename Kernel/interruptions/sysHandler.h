#ifndef __SYSHANDLER_H__
#define __SYSHANDLER_H__
#include <stdint.h>
#include <naiveConsole.h>
#include <keyboard.h>

void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2);
void read(uint64_t r1, uint64_t r2);

#endif