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
char user[2][MAX_SIZE/2];
int uIndex[2];
int cB;
char c = 0;
int firstTab;

void (*func_ptr[COMMANDS_SIZE])() = {help, getTime, inforeg, getMem, cpuid,  exc0Trigger, exc6Trigger, quadratic , clear};

void shell() {
    clear(0);
    clear(1);
    cB = 0;
    _changeScreen(cB);
    firstTab = 1;
    requestUser();
    printf("%s: $ ", user[cB]);

    while(!exit) {

        c = getChar();

        if( c == ESC ) {
            exit = 1;
        }
        else if( c == TAB ){
            cB = (cB == 0) ? 1 : 0;
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
                if(isCommand == 3)
                    func_ptr[isCommand](parameter[cB]);
                else if(isCommand == 8)
                    func_ptr[isCommand](cB);
                else
                    func_ptr[isCommand]();
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
    printf("Bienvenido %s, si quiere cambiar a la otra terminal presione TAB\n", user[cB]);
}
