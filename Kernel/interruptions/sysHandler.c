#include <sysHandler.h>
#include <naiveConsole.h>

void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2){
    switch (sysNumber)
    { 
        case 0: //sysRead  r1=buffer r2=10
            read((unsigned char *)r1, (unsigned int)r2);
            break;
        case 1: // sysWrite 
            ncPrint((const char *) r1, r2); //en r1 iria un string y en r2 el fd 
            break;
        case 2: // sysGetTime
            getTime((int* ) r1,(int *) r2); // en r1 dia mes año y en r2 horas min seg
            break;
        case 3: //sysGetReg 
            getReg((uint64_t *) r1 );
            break;
        case 4: //sysGetMem
            getMem((uint32_t * ) r1,(uint32_t * ) r2);
        default: 
            //potncial print error
            break;
    }
}

void read(unsigned char * r1, unsigned int r2) {
    unsigned char * KeyBuffer = getBuffer(); 
    unsigned int i;
    r1[0] = 0;
    for(i = 0; KeyBuffer[i]!= 0 && i < r2; i++) {
        r1[i] = KeyBuffer[i];
    }
    removeBuffer();  
}

void getTime(int * r1, int * r2) {
    r2[0] = _RTC(0); //segundo
    r2[1] = _RTC(2); //minuto
    r2[2] = _RTC(4); //hora
    r1[0] = _RTC(7); //dia
    r1[1] = _RTC(8); //mes
    r1[2] = _RTC(9); //año

    // ACLARAR QUE ESTO LO SACAMOS DE INTERNET  https://wiki.osdev.org/CMOS#Format_of_Bytes
    r2[0] = (r2[0] & 0x0F) + ((r2[0] / 16) * 10);
    r2[1] = (r2[1] & 0x0F) + ((r2[1] / 16) * 10);
    r2[2] = ((r2[2] & 0x0F) + (((r2[2] & 0x70) / 16) * 10) ) | (r2[2] & 0x80);
    r1[0] = (r1[0] & 0x0F) + ((r1[0] / 16) * 10);
    r1[1] = (r1[1] & 0x0F) + ((r1[1] / 16) * 10);
    r1[2] = (r1[2] & 0x0F) + ((r1[2] / 16) * 10);
}

void getReg(uint64_t * r1 ){
    _getRegisters(r1); // Despues ver si conviene hacerla en C 
}

void getMem(uint32_t * dir, uint32_t * vec) {
    // falta chequear los rangos accesibles 
    for(int i = 0; i < 8; i++){
        vec[i] = *(dir + i*4);
    }
}