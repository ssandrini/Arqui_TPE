#include <lib2.h>
#include <stdarg.h>  


int scanf() {
    return 0;
}

void printf(char* format,...) 
{ 
    char *fpointer; 
    int i; 
    unsigned int index = 0;
    char * aux; 
    char ans[256];

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(fpointer = format; *fpointer != '\0'; fpointer++) 
    { 
        while( *fpointer != '%' ) 
        { 
            ans[index++] = *fpointer;
            fpointer++; 
        } 

        fpointer++; // salteamos el porcentaje

        //Module 2: Fetching and executing arguments
        switch(*fpointer) 
        { 
            case 'c' : 
                i = va_arg(arg,int);     //Fetch char argument
                ans[index++] = i;
                break; 

            case 'd' : 
                i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                if(i<0) 
                { 
                    i = -i;
                    ans[index++] = '-';
                } 
                *aux = 0;
                intToBase(i,aux,10);
                while(*aux != 0) {
                    ans[index++] = *aux;
                    aux++;
                }
                break; 

            case 's': 
                aux = va_arg(arg,char *);       //Fetch string
                while(*aux != 0) {
                    ans[index++] = *aux;
                    aux++;
                }
                break; 

            case 'x': 
                i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                *aux = 0;
                intToBase(i,aux,16);
                while(*aux != 0) {
                    ans[index++] = *aux;
                    aux++;
                }
                break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
    _write(ans);
    return;
} 

void putChar(const char ascii){
    char toPrint[2];
    toPrint[0] = ascii;
    toPrint[1] = 0;
    _write(toPrint);
}

char getChar() {
    char * ans=0;
    _getBuffer(ans,1);
    return ans[0];
}


int intToBase(int value, char * buffer, unsigned int base)
{
	char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	//Calculate characters for each digit
	do
	{
		int remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}




//size_t read(int fd, void *buf, size_t count);

// >> asd
// >> comando desconocido 
// >> HOLA. INGRESE SU USERNAME:
// sol
// >> llokk