#include <naiveConsole.h>

void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2){
    switch (sysNumber)
    {
        case 1: // sysWrite
            ncPrint((const char *) r1, r2); //en r1 iria un string y en r2 el fd
            break;
    
        default:
            //potncial print error
            break;
    }
}