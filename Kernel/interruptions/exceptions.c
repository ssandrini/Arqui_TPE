#include <naiveConsole.h>
#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	ncPrint("zero division error",0);
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