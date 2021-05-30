#include <commands.h>

#define COMMANDS_SIZE 8
#define CASE_GETMEM 3
#define LENGTH_PRINTMEM 8

char commandsNames[8][20] = {"help", "time", "inforeg", "printmem", "cpuid", "trigger0", "trigger6", "quadratic"};
char info[3][150] = {"inforeg: imprime en pantalla el valor de todos los registros \n",
"printmem DIR : realiza un volcado de memoria de 32 bytes a partir de la direccion recibida como argumento \n",
"time: desplega el dia y la hora del sistema\n"};

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
    static const char *registersName[] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15"};
    //NOS FALTAN "RIP" "CS" "FLAGS" "RSP"
    _getReg((uint64_t) registers);
    for(int i = 0, j=14; i < 15; i++, j--) {
         if( i > 0 && i % 3 == 0)
            printf("\n");
         printf("%s : %xh    ", registersName[i], registers[j]);
    }
    printf("\n");
}

void getMem(char * param) {
    uint32_t * dir = hexaStrToDir(param);
    for(int i = 0; i < 8; i++) {
        *(dir+i*4) = i;
    }
    uint32_t vec[8];
    _getMem(dir, vec);
    printf("mem: \n");
    for(int i = 0; i<8;i++) {
        if( i > 0 && i % 4 == 0) 
            printf("\n");
        printf("%xh    ", vec[i]);
    }
    printf("\n");

}

void exc0Trigger() {
    ;
}

void exc6Trigger() {
    ;
}

int checkCommand(char * buffer, char * parameter) {
    char aux[LENGTH_PRINTMEM];
    for(int i = 0; i < COMMANDS_SIZE; i++) { //printmem 45892
        if(i == CASE_GETMEM){
            int j = 0;
            for(; j < LENGTH_PRINTMEM; j++){
                aux[j] = buffer[j];
            }
            aux[j] = 0; 
            if(strcmp(aux, commandsNames[i]) == 0 && buffer[LENGTH_PRINTMEM] == ' '){
                j=LENGTH_PRINTMEM+1;
                while(buffer[j] != 0){
                    if ((buffer[j] >= '0' && buffer[j] <= '9') || (buffer[j] >= 'A' && buffer[j] <= 'Z')){
                        *parameter++ = buffer[j++];
                    }
                    else
                        return -1;
                }
                *parameter = 0;

                return i;
            }
        }
        else if( strcmp(buffer, commandsNames[i]) == 0 )
            return i;
    }
    return -1;
}

// int quadratic() {
//     // aca en realidad debería hacer un scan f para cada coeficiente, por ahora 
//     // los puse fijos para probar
//     long double r1, r2, a, b, c;
//     a = (long double) 1;
//     b = (long double) -2;
//     c = (long double) -10;    
//     int aux = _quadratic(&a,&b,&c, &r1,&r2);
//     if(aux == 0) {
//         printf("No se pudo encontrar las raices\n");
//     } else {
//         printf("las encontre, todavia no tenemos hecho el soporte para %Lf");
//         // printf("r1: %Lf %Lf \n",r1,r2);
//     }
//     //return aux;?
// }