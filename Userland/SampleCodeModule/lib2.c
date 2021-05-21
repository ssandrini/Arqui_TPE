#include <lib2.h>

int scanf() {
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

unsigned char getChar() {
    unsigned char * ans=0;
    _getBuffer(ans,1);
    return ans[0];
}

//size_t read(int fd, void *buf, size_t count);

// >> asd
// >> comando desconocido 
// >> HOLA. INGRESE SU USERNAME:
// sol
// >> llokk