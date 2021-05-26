#include <lib2.h>
#include <stdarg.h>  

int scanf() {
    return 0;
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


 //https://www.techiedelight.com/implement-itoa-function-in-c/
 // Iterative function to implement itoa() function in C
char *numToStr(int value, char *buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
        return buffer;
    // consider absolute value of number
    int n = value;
    if(n < 0) {
        n = -n;
    }
    int i = 0;
    while (n)
    {
        int r = n % base;
        if (r >= 10)
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;

        n = n / base;
    }
    // if number is 0
    if (i == 0)
        buffer[i++] = '0';
    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';
    buffer[i] = '\0'; // null terminate string
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

char *reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);
    return buffer;
}

void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}


char *strcpy(char *destination, const char *source)
{
    char *ptr = destination;
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return ptr;
 }

void printf(char *str, ...)
{
    va_list args;
    int i = 0,h=0, j = 0;  // i lectura en str  - j pos en buffer
    char buff[100] = {0}, tmp[20];
    char *str_arg;
    char * hexa_arg;
    va_start(args, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
                case 'c':
                {
                    buff[j] = (char)va_arg(args, int);
                    j++;
                    break;
                }
                case 'd':
                {
                    numToStr(va_arg(args, int),tmp,10); //base 10
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 's':
                {
                    str_arg = (char *)va_arg(args, char *);
                    strcpy(&buff[j], str_arg);
                    j += strlen(str_arg);
                    break;
                }
                case 'x':
                {
                    numToStr(va_arg(args, int),tmp,16); //base 16
                    strcpy(&buff[j+h], tmp);
                    j += strlen(tmp);
                    break;
                }
            }
        }
        else
        {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    _write(buff);
    va_end(args);
}
































































































































































































































































/*
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
                fpointer++;
            }  
        } 
    } 

    ans[index] = 0;
    va_end(arg); 
    _write(ans);
    return;
} 

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

*/