#include <naiveConsole.h>
#include <exceptions.h>
#include <time.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPERATION_ID 6

// valores de retorno de la excepcion
uint64_t * ipReturn;
uint64_t * rspReturn;

void exceptionDispatcher(uint64_t exception, uint64_t * stackFrame) {
	// por ahora manejamos estas dos excepciones	
	if (exception == (uint64_t) 0 ) {
		zero_division();
	}
	else if(exception == INVALID_OPERATION_ID)
		invalid_operation();
	// en todas se imprimen los registros y se resetea
	registerPrint(stackFrame);
	// para resetear cambiamos aca los valoress de los registros
	stackFrame[0xF] = (uint64_t)ipReturn;
	stackFrame[0x12] = (uint64_t)rspReturn;
	return;
}

// setea los registros de retorno
void setAddresses(uint64_t * ip, uint64_t * rsp) {
	ipReturn = ip;
	rspReturn = rsp;
}

void invalid_operation(){
	ncPrint("Invalid code of operation", 0);
	ncNewline();
}

void zero_division() {
	ncPrint("Zero division error ",0);
	ncNewline();
}

void registerPrint(uint64_t * stackFrame) {
	char buffer[9];
	static const char *registersName[] = { "R15:   ", "R14:   ", "R13:   ", "R12:   ", "R11:   ", "R10:   ", "R9:    ", "R8:    ", "RSI:   ", "RDI:   ", "RBP:   ", "RDX:   ", "RCX:   ", "RBX:   ", "RAX:   ", "RIP:   ", "CS:    ", "FLAGS: ", "RSP:   "};
	for (int i = 0; i < 19; i++) {
		ncPrint(registersName[i],0);
		uintToBase(stackFrame[i], buffer, 16);
		intToHexaStr(buffer);
		ncPrint(buffer,0);
		if (i> 0 && i % 3 == 0) {
			ncNewline();
		} else {
			ncPrint("  ",0);
		}
	}
	_sti();
	ncPrint("La pantalla se reiniciara en ",0);
	char buff[3] = {0};
	// espera a una interrupcion
	_hlt();
	int init_time = seconds_elapsed();
	int aux = 10;
	int i = 10;
	uintToBase(i, buff, 10);
	ncPrint(buff,0);
	while (i > 0) {
		_hlt();
		aux = 10 - (seconds_elapsed() - init_time);
		if (i != aux) {
			ncPrintChar(-10,0xD);
			if (i == 10) {
				ncPrintChar(-10,0xD);
			}
			i = aux;
			uintToBase(i, buff, 10);
			ncPrint(buff, 0);
		}
	}
	ncNewline();
}

/*
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
	*/