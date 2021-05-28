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
int numToStr(int value, char *buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
        return -1;
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
    reverse(buffer, 0, i - 1);
    return i;
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
    int i = 0,h, j = 0;  // i lectura en str  - j pos en buffer
    int forindex;
    char buff[100] = {0}, tmp[20], tmp2[8];
    char *str_arg;
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
                    h = numToStr(va_arg(args, int),tmp,16); //base 16
                    for(forindex = 0; forindex < 8-h; forindex++) {
                        tmp2[forindex] = '0';
                    }
                    strcpy(&tmp2[forindex], tmp);
                    strcpy(&buff[j], tmp2);
                    j += strlen(tmp2);
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

int strcmp(char *s1, char *s2){
    int i = 0;
      while(s1[i] == s2[i])
      {
          if(s1[i] == '\0' && s2[i] == '\0')
              return 0; //si llego hasta aca es porque son exactamente iguales
        i++;
    }
    return s1[i] - s2[i]; //si llego aca es que son distintos
}

