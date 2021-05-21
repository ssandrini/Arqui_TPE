#include <sysHandler.h>
#include <naiveConsole.h>

void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2){
    switch (sysNumber)
    { 
        case 0: //sysRead  r1=buffer r2=10
            read(r1, r2);
            break;
        case 1: // sysWrite 
            ncPrintChar((const char) r1, r2); //en r1 iria un string y en r2 el fd 
            break;
        default: 
            //potncial print error
            break;
    }
}
//a00000
//000000
void read(uint64_t r1, uint64_t r2) {
    unsigned char * KeyBuffer = getBuffer(); 
    unsigned int i;
    ((unsigned char *)r1)[0] = 0;
    for(i = 0; KeyBuffer[i]!= 0 && i < (unsigned int) r2; i++) {
        ((unsigned char *) r1)[i] = KeyBuffer[i];
    }
    removeBuffer();  
}

// int i expression must have pointer-to-object type but it has type "int"
