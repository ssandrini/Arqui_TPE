#include <lib2.h>
#include <stdarg.h>  

int scanf() {
    return 0;
}

void printf(char * format,...) 
{ 
    char * fpointer; 
    int i; 
    unsigned int index = 0;
    char * aux; 
    char ans[256];

    va_list arg; 
    va_start(arg, format); 

    for(fpointer = format; *fpointer != '\0'; fpointer++) 
    { 
        if(*fpointer != '%') 
        { 
            ans[index++] = *fpointer;
        } 
        else {
            fpointer++; // salteamos el porcentaje
            switch(*fpointer) 
            { 
                case 'c' : 
                    i = va_arg(arg,int);     
                    ans[index++] = i;
                    break; 

                case 'd' : 
                    i = va_arg(arg,int);         
                    itoa(i,aux,10);
                    while(*aux != 0) {
                        ans[index++] = *aux;
                        aux++;
                    }
                    break; 

                case 's': 
                    aux = va_arg(arg,char *);      
                    while(*aux != 0) {
                        ans[index++] = *aux;
                        aux++;
                    }
                    break; 

                case 'x': 
                    i = va_arg(arg,int);         
                    itoa(i,aux,16);
                    while(*aux != 0) {
                        ans[index++] = *aux;
                        aux++;
                    }
                    break; 
            }  
        } 
    } 

    ans[index] = 0;
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

 int strlen(const char * string) {
     int i = 0;
     while(*string++ != 0) {
         i++;
     }
     return i;
 }
//////////////////////// SANTI /////////////////////////////////////
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = value;;
    if(n < 0)
        n = -n;
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

//////////////////////// FIN SANTI///////////////////////////////////////////////////////
