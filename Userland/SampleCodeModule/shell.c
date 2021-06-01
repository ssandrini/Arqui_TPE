#include <shell.h> 
#define MAX_SIZE 100
#define ESC 1
#define TAB -12
int exit = 0;
char buffer[2][MAX_SIZE];
char parameter[2][MAX_SIZE];
int bIndex[2];
int cB = 0; 
char c = 0;
int Tflag = 0;
void shell() {
    while(!exit) {
        do {
            c = getChar();
        } while(c == 0);

        if( c == ESC ) {
            exit = 1;
        }
        else if( c == TAB ){
            if(cB == 0){
                cB++;
            }
            else{
                cB--;
            }
            _changeScreen(cB);
        }
        else if( c == '\n') {
            putChar(c);
            int isCommand = checkCommand(buffer[cB], parameter[cB]);//el uno por default 
            buffer[cB][0] = 0;
            bIndex[cB] = 0;
            if(isCommand >= 0) {
                switch(isCommand) {
                    case 0: help(); break;
                    case 1: getTime(); break;
                    case 2: inforeg(); break;
                    case 3: getMem(parameter[cB]); break;
                    case 5: exc0Trigger();break;
                    case 6: exc6Trigger();break;
                    case 8: clear(cB);break;
                    default: break;
                }
                parameter[cB][0] = 0;
            }
            else {
                printf("El comando ingresado es invalido\n");
            }
        }
        else if (c != 0 ) {
            if(c == -10) {
                if(bIndex[cB]>0){
                    putChar(c);
                    buffer[cB][--bIndex[cB]] = 0;
                }
            }
            else {
               putChar(c);
               buffer[cB][bIndex[cB]++] = c;
               buffer[cB][bIndex[cB]] = 0;
            }
        }     
    }
    printf("chau\n");
    return;
}

