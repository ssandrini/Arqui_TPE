#include <shell.h> 
#define MAX_SIZE 100
#define ESC 1
#define TAB -12
#define BSPACE -10
int exit = 0;
int exitUser;
char buffer[2][MAX_SIZE];
char parameter[2][MAX_SIZE];
int bIndex[2];
char user[2][MAX_SIZE/2] ={0};
int uIndex[2];
int cB = 0;
char c = 0;
int Tflag = 0;
int firstTab = 1;
void shell() {
    
    requestUser();
    printf("%s: $ ", user[cB]);

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
            if(firstTab){
                requestUser();
                printf("%s: $ ", user[cB]);
                firstTab = 0;
            }
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
            printf("%s: $ ", user[cB]);
        }
        else if (c != 0 ) {
            if(c == BSPACE) {
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

void requestUser(){
    uIndex[cB] = 0;
    exitUser = 0;
    printf("Bienvenido, ingrese su usuario: ");
    while( !exitUser ){

        do {
            c = getChar();
        } while(c == 0);

        if(c == '\n' || c == ESC){
            exitUser = 1;
            if(c == ESC){exit = 1;}
        }
        else if(c == TAB){
            ;//si oprime TAB mientras escribe el usuario no hace nada
        }
        else if(c == BSPACE){
            if(uIndex[cB]>0){
                putChar(c);
                user[cB][--uIndex[cB]] = 0;
            }
        }else{
            user[cB][uIndex[cB]++] = c;
            user[cB][uIndex[cB]] = 0;
            putChar(c);
        }

    }
    clear(cB);
}
