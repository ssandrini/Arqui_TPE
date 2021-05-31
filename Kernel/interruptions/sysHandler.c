#include <sysHandler.h>
#include <naiveConsole.h>

void sysHandler(uint64_t sysNumber, uint64_t r1, uint64_t r2){
    switch (sysNumber)
    { 
        case 0: // sysRead  r1=buffer r2=10
            read((unsigned char *)r1, (unsigned int)r2);
            break;
        case 1: // sysWrite 
            ncPrint((const char *) r1, r2); //en r1 iria un string y en r2 el fd 
            break;
        case 2: // sysGetTime
            getTimeRTC(r1, r2); // en r1 dia mes año y en r2 horas min seg
            break;
        case 3: // sysGetReg 
            getReg((uint64_t *) r1);
            break;
        case 4: // sysGetMem
            getMem((uint32_t * ) r1,(uint32_t * ) r2);
            break;
        case 5: // sysChangeScreen
            changeScreen((int) r1);
            break;
        case 6: // sysClearScreen
            clearScreen(); 
            break;
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

// EN R1 VIENE DATE, EN R2 VIENE HOUR
void getTimeRTC(uint64_t r1, uint64_t r2) {
    int * buffer1 = (int *) r1;
    int * buffer2 = (int *) r2;
    buffer1[0] = _RTC(9); //año
    buffer1[1] = _RTC(8); //mes
    buffer1[2] = _RTC(7); //dia
    buffer2[0] = _RTC(4); //hora
    buffer2[1] = _RTC(2); //minuto
    buffer2[2] = _RTC(0); //segundo

    // ACLARAR QUE ESTO LO SACAMOS DE INTERNET  https://wiki.osdev.org/CMOS#Format_of_Bytes
    buffer2[2] = (buffer2[2] & 0x0F) + ((buffer2[2] / 16) * 10);
    buffer2[1] = (buffer2[1] & 0x0F) + ((buffer2[1] / 16) * 10);
    buffer2[0] = ((buffer2[0] & 0x0F) + (((buffer2[0] & 0x70) / 16) * 10) ) | (buffer2[0] & 0x80);
    buffer1[2] = (buffer1[2] & 0x0F) + ((buffer1[2] / 16) * 10);
    buffer1[1] = (buffer1[1] & 0x0F) + ((buffer1[1] / 16) * 10);
    buffer1[0] = (buffer1[0] & 0x0F) + ((buffer1[0] / 16) * 10);
}

void getReg(uint64_t * registers){
    _getRegisters(registers); // Despues ver si conviene hacerla en C 
}

void getMem(uint32_t * dir, uint32_t * vec) {
    // falta chequear los rangos accesibles 
    for(int i = 0; i < 8; i++){
        vec[i] = *(dir + i*4);
    }
}

void clearScreen() {
    ncClear();
}