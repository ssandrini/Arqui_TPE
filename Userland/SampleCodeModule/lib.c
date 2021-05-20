#include <lib.h>

char * scanf() {
    return 0;
}
void printf(const char * string){
    int i = 0;
    while(string[i] != 0) {
        putChar(string[i++]);
    }
}

void putChar(const char ascii){
    _write(ascii);
}

char getChar() {
    //return _getKey();
    return 'a';
}


// >> asd
// >> comando desconocido 
// >> HOLA. INGRESE SU USERNAME:
// sol
// >> llokk