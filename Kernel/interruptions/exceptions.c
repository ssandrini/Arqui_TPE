#include <naiveConsole.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPERATION_ID 6

static void zero_division();

void exceptionDispatcher(int exception, uint64_t * stackFrame) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(stackFrame);
	if(exception == INVALID_OPERATION_ID)
		invalid_operation(stackFrame);
	//habria que imprimit los registros
	//hay que resetear la pantalla
	return;

	//en el main del kernel se envian los valores iniciales del RSP y de la primera y 
	//se ejecuta la instruccion para el reinicio luego de una excepcion: setAddresses((uint64_t *)sampleCodeModuleAddress, getRSP());

	//En lib.asm
	//getRSP:
	//mov rax, rsp
	//ret

	//void setAddresses(uint64_t * ip, uint64_t * rsp) {
	//ipReturn = ip;
	//rspReturn = rsp;
	//}
}

static void invalid_operation(uint64_t * stackFrame){
	ncPrint("Invalid code of operation", 0);
	ncNewline();
}

static void zero_division(uint64_t * stackframe) {
	ncPrint("Zero division error ",0);
	ncNewline();
}


/*
void exception0test() {
	int a = 4/0;		<- RIP
	printf("hola");			
	printf("hola2");
	return;
}
RIP -> 
RSP -> ret 


*/