#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include <lib2.h>
#include <stdint.h>

#define COMMANDS_SIZE 9
#define CASE_GETMEM 3
#define LENGTH_PRINTMEM 8
#define SPECIAL_FEATURES_ID 1
#define FEATURES_ID 0
void help();
void inforeg();
void getMem(char * param);
void getTime();
int checkCommand(char * buffer, char * parameter);
void exc0Trigger();
void exc6Trigger();
void clear(int cB);
void quadratic();
void cpuid();
extern int _quadratic(long double * a, long double * b, long double * c, long double * r1, long double * r2);
extern void _exc6Trigger();
extern void _getReg(uint64_t registers);
extern void _getMem(uint32_t * dir, uint32_t * memory);
extern void _getTime(int * date, int * hours);
extern void _clearScreen(int cB);
extern int _getCpuInfo(uint32_t reg1, uint32_t reg2, int features_id);

#endif