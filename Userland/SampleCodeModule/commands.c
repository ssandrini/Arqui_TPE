#include <commands.h>

char commandsNames[9][20] = {"help", "time", "inforeg", "printmem", "cpuid", "trigger0", "trigger6", "quadratic","clear"};
char info[3][150] = {"inforeg: imprime en pantalla el valor de todos los registros \n",
"printmem DIR : realiza un volcado de memoria de 32 bytes a partir de la direccion recibida como argumento \n",
"time: desplega el dia y la hora del sistema\n"};

void help() {
    for(int i = 0; i < 3; i++){
        printf("%s",info[i]);
    }
}

void clear(int cB) {
    _clearScreen(cB);
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
    uint64_t registers[19];
    static const char *registersName[] = { "R15:   ", "R14:   ", "R13:   ", "R12:   ", "R11:   ", "R10:   ", "R9:    ", "R8:    ", "RSI:   ", "RDI:   ", "RBP:   ", "RDX:   ", "RCX:   ", "RBX:   ", "RAX:   ", "RIP:   ", "CS:    ", "FLAGS: ", "RSP:   "};
    _getReg((uint64_t) registers);
    for(int i = 0; i < 19; i++) {
         if( i > 0 && i % 3 == 0)
            printf("\n");
         printf("%s : %xh    ", registersName[i], registers[i]);
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
    int a = 5/0;
}

void exc6Trigger() {
    _exc6Trigger();
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

void quadratic() {
    // aca en realidad debería hacer un scan f para cada coeficiente, por ahora 
    // los puse fijos para probar
    long double r1, r2, a, b, c;
    a = (long double) 1;
    b = (long double) -2;
    c = (long double) -10;  
    int aux = _quadratic(&a,&b,&c, &r1,&r2);
    if(aux == 0) {
        printf("No se pudo encontrar las raices\n");
    } else {
        printf("las encontre, todavia no tenemos hecho el soporte para % Lf\n");
        // printf("r1: %Lf %Lf \n",r1,r2);
    }
    //return aux;?
}

void cpuid() {
    uint32_t r1; 
    uint32_t r2;

    uint32_t masks1[8]= {     0x1,             0x2,             0x1000,        0x80000,        0x100000,       0x2000000,      0x10000000,     0x20000000};
    char namesr1[8][20] = { "sse3_support", "pclmulqdq_support", "fma_support", "sse41_support", "sse42_support", "aesni_support", "avx_support", "f16c_support"};
//              bit =        0                   1                 12              19               20              25              28              29


    uint32_t masks2[3] = {0x800000,    0x2000000,      0x4000000};
    char namesr2[3][20] = {"mx_support", "sse_support", "sse2_support"};
//              bit =       23              25          26


    uint32_t sMasks1[2] = {   0x200     ,        0x400        };
    char snamesr1[2][20] = {"vaesni_support", "vpclmulqdq_support"};
//              bit =           9                  10


    uint32_t sMasks2 =   0x20;
    char * snamesr2 = "avx2_support"; 
//              bit =     5


    int ok = FEATURES_ID;
    _getCpuInfo(&r1, &r2, &ok); 
    printf("ok = %d ", ok);
    if(ok) {
        printf("cpuid_support : 1 \n");
    }
    else {
        printf("cpuid_support : 0 \n");
        return;
    }

    int aux;
   printf("%x \n", (int) r1);
   printf("%x \n", (int) r2);
    for(int i = 0; i < 8; i++){
        if( masks1[i] & r1 > 0 )
            aux = 1;
        else
            aux = 0;
        if( i > 0 && i % 3 == 0 )
            printf("\n");

        printf("%s : %d  ", namesr1[i], aux);
        
    }
    

    for(int i = 0; i < 3; i++){
        if( masks2[i] & r2 > 0 )
            aux = 1;
        else
            aux = 0;
        if( i == 2 )
            printf("\n");

        printf("%s : %d  ", namesr2[i], aux);
    }
    
    printf("\n");   
    printf("%x \n", (int) r1);
    printf("%x \n", (int) r2);

    ok = SPECIAL_FEATURES_ID;
    _getCpuInfo(&r1, &r2, &ok);
    
    for(int i = 0; i < 2; i++){
        if( sMasks1[i] & r1 > 0 )
            aux = 1;
        else
            aux = 0;
        if( i == 1 )
            printf("\n");

        printf("%s : %d  ", snamesr1[i], aux);
    }
    printf("\n");
    printf("%s : %d \n", snamesr2, (sMasks2 & r2 > 0 )? 1 : 0); 

    printf("%x \n", (int) r1);
    printf("%x \n", (int) r2);
    
}