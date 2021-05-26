#include <commands.h>

char info[3][150] = {"inforeg: imprime en pantalla el valor de todos los registros \n",
"printmem DIR : realiza un volcado de memoria de 32 bytes a partir de la direccion recibida como argumento \n",
"time: desplega el dia y la hora del sistema"};

void help() {
    for(int i = 0; i < 3; i++){
        printf("%s",info[i]);
    }
}

/*
void inforeg() {
    uint64_t registers[15];
    _getReg((uint64_t) registers);

    for(int i = 0; i < 15; i++) {
         printf("%x \n", registers[i]);
    }
}

void getMem(){
    uint32_t * dir = 180000;
	uint32_t vec[8];
    _getMem(dir, vec);
    for(int i = 0; i<8;i++) {
        printf("%x ", vec[i]);
	}
}
*/
void getTime() {
    int date[3]; int hour[3];
    _getTime(date,hour);
    printf("fecha: \n");
    for(int i = 0; i < 3; i ++) {
        printf("%d   ", date[i]);
    }
    printf("\n hora: \n");
    for(int i = 0; i < 3; i ++) {
        printf("%d   ", date[i]);
    }
}

////     int fecha[3]; int hora[3];
////     sysHandler((uint64_t) 2, (uint64_t) fecha, (uint64_t) hora);


// uint64_t registros[15];
// sysHandler((uint64_t) 3, (uint64_t) registros, (uint64_t)  73);

