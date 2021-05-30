#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include <lib2.h>
#include <stdint.h>


void help();
void inforeg();
void getMem();
void getTime();
int checkCommand(char * buffer);
//int quadratic();
//extern int _quadratic(long double a, long double b, long double c, long double r1, long double r2);
extern void _getReg(uint64_t registers);
extern void _getMem(uint32_t * dir, uint32_t * memory);
extern void _getTime(int * date, int * hours);

#endif