#include <shell.h> 
#define MAX_SIZE 512
#define ESC 1
int exit = 0;
char inputBuffer[MAX_SIZE];
int bIndex = 0;

void shell() {

    while(!exit) {
        char c = getChar();
        if( c == ESC ) {
            exit = 1;
        }
        else if( c == '\n') {
            putChar(c);
            int isCommand = checkCommand(inputBuffer);
            inputBuffer[0] = 0;
            bIndex = 0;
            if(isCommand >= 0){
                switch(isCommand) {
                    case 0: help(); break;
                    case 1: getTime(); break;
                    case 2: inforeg(); break;
                    case 3: getMem(); break;
                    default: break;
                }
            }
            else {
                printf("El comando ingresado es invalido\n");
            }
        }
        else if (c != 0 ) { 
            putChar(c);
            if(c == -10) {
                inputBuffer[--bIndex] = 0;
            }
            inputBuffer[bIndex++] = c;
            inputBuffer[bIndex] = 0;
        }        
    }

    // hol
    //    3
    printf("chau\n");
    return;
}

// tenemos un error al querer borrar en la shell, no se borra el caracter