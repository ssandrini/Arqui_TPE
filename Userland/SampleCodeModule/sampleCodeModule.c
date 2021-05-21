/* sampleCodeModule.c */
#include <lib2.h>

int main() {
	
	printf("Hola");
	while(1) {
		unsigned char a = getChar();
		if(a != 0)
			putChar(a); 
	}
	return 0xDEADBEEF;
}