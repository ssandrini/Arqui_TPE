#include <commands.h>

char info[3][150] = {"inforeg: imprime en pantalla el valor de todos los registros \n",
"printmem DIR : realiza un volcado de memoria de 32 bytes a partir de la direccion recibida como argumento \n",
"time: desplega el dia y la hora del sistema"};

void help() {
    for(int i = 0; i < 3; i++){
        printf("%s",info[i]);
    }
}

void getTime() {
    int date[3]; int hour[3]; 
    _getTime(date,hour);
    printf("fecha: ");
    printf(" %d : %d : %d \n", date[2], date[1], date[0]);
    printf("hora: ");
    printf(" %d : %d : %d \n", hour[0], hour[1], hour[2]);
}

void inforeg() {
    uint64_t registers[15];
    _getReg((uint64_t) registers);

    for(int i = 0; i < 15; i++) {
         printf("%d \n", registers[i]);
    }
}


void getMem() {
    uint32_t * dir = 1800000;
    /*
    for(int i = 0; i < 8; i++) {
        *(dir+i*4) = i;
    }
    */
	uint32_t vec[8];
    _getMem(dir, vec);
    printf("mem: ");
    for(int i = 0; i<8;i++) {
        printf("%d ", vec[i]);
	}
}

void exc0Trigger() {
    ;
}

void exc6Trigger() {
    ;
}
