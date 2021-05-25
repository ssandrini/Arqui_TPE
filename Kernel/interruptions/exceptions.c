#include <naiveConsole.h>
#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception, uint64_t * stackFrame) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(stackFrame);
	ncPrint("HOLA",0);
	return;
}

static void zero_division(uint64_t * stackframe) {
	ncPrint("zero division error ",0);
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