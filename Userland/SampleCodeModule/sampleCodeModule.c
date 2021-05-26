/* sampleCodeModule.c */
 #include <lib2.h>


void testZero(){
	int a=1, b=0;
	a = a/b;
	return;
}

int main() {

	//char * m = "mundo";
	//printf("a ver si esto anda");
	//printf("hola %s %d", m, 10);
	/*while(1) {
		unsigned char a = getChar();
		if(a !=0){
			putChar(a); 
		}
	}
	*/
	//testZero();

	printf("a ver si esto %s %d %x puntos \n","anda",10, 0xAFD56);
	putChar('x');
	printf("\n%d",strlen("asd"));
	
	return 0;
}