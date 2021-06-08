#include <lib2.h>
#include <stdarg.h>

#define BSIZE 50
#define BSPACE -10
char auxBuffer[BSIZE] = {0};
int currentIdx=0;

void putChar(const char ascii)
{
    char toPrint[2];
    toPrint[0] = ascii;
    toPrint[1] = 0;
    _write(toPrint, 0xFFFFFF);
}

char getChar()
{
    char k = 0;
    _getBuffer(&k, 1);
    return k;
}

int strlen(const char *string)
{
    int i = 0;
    while (*string++ != 0)
    {
        i++;
    }
    return i;
}

//https://www.techiedelight.com/implement-itoa-function-in-c/
// Iterative function to implement itoa() function in C
int numToStr(int value, char *auxBuffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
        return -1;
    // consider absolute value of number
    int n = value;
    if (n < 0)
    {
        n = -n;
    }
    int i = 0;
    while (n)
    {
        int r = n % base;
        if (r >= 10)
            auxBuffer[i++] = 65 + (r - 10);
        else
            auxBuffer[i++] = 48 + r;

        n = n / base;
    }
    // if number is 0
    if (i == 0)
        auxBuffer[i++] = '0';
    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        auxBuffer[i++] = '-';
    auxBuffer[i] = '\0'; // null terminate string
    // reverse the string and return it
    reverse(auxBuffer, 0, i - 1);
    return i;
}

char *reverse(char *auxBuffer, int i, int j)
{
    while (i < j)
        swap(&auxBuffer[i++], &auxBuffer[j--]);
    return auxBuffer;
}

void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}

void strcpy(char *destination, const char *source)
{
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return;
}

void printf(char *str, ...)
{
    va_list args;
    int i = 0, h, j = 0; // i lectura en str  - j pos en auxBuffer
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
                numToStr(va_arg(args, int), tmp, 10); //base 10
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
                h = numToStr(va_arg(args, int), tmp, 16); //base 16
                for (forindex = 0; forindex < 8 - h; forindex++)
                {
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
    _write(buff,0xFFFFFF);
    va_end(args);
}

int strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] == s2[i])
    {
        if (s1[i] == '\0' && s2[i] == '\0')
            return 0; //si llego hasta aca es porque son exactamente iguales
        i++;
    }
    return s1[i] - s2[i]; //si llego aca es que son distintos
}

//https://www.geeksforgeeks.org/write-your-own-atoi/
int strToInt(char *str)
{
    int len = strlen(str);
    int ans = 0;
    int j = 0;
    int minusFlag = 0 ;
    if(str[0] == '-')
        minusFlag = 1;
    for (int i = len - 1; i >= 0; i--, j++)
    {
        if (str[i] <= '9' && str[i] >= '0')
        {
            ans += (str[i] - '0') * pow(10, j);
        }
    }
    if(minusFlag)
        ans = -ans;
    return ans;
}

uint32_t *hexaStrToDir(char *hexaStr)
{ // los caracteres ya tienen que ser validos
    int len = strlen(hexaStr);
    uint32_t *ans = 0;
    int j = 0;
    for (int i = len - 1; i >= 0; i--, j++)
    {
        if (hexaStr[i] <= '9' && hexaStr[i] >= '0')
        {
            ans += (hexaStr[i] - '0') * pow(16, j);
        }
        else if (hexaStr[i] <= 'F' && hexaStr[i] >= 'A')
        {
            ans += (hexaStr[i] - 'A') * pow(16, j);
        }
    }
    return ans;
}

int pow(int base, int e)
{
    int ans = 1;
    for (int i = 0; i < e; i++)
    {
        ans *= base;
    }
    return ans;
}

void doubleToString(long double result, char *auxBuffer)
{
    int isNegative = (result < 0) ? 1:0;
    int integer_part = (int)result;
    
    result = (result - integer_part) * pow(10, 8);
    int decimal_part = (int)result;
    
    char aux[40];
    if (isNegative == 1) {
        decimal_part = -decimal_part;
        if(integer_part == 0) {
            *aux = '-';
            int len = numToStr(integer_part, aux+1, 10);
            aux[len+1] = '.';
            numToStr(decimal_part, aux + len + 2, 10);
            strcpy(auxBuffer, aux);
            return;
        }
    }
    int len = numToStr(integer_part, aux, 10);
    aux[len] = '.';
    numToStr(decimal_part, aux + len + 1, 10);
    strcpy(auxBuffer, aux);
}


int readNumFromLine(char * dest)
{
    auxBuffer[0] = 0;
    currentIdx = 0;
    int c;
    int pointFlag=0;
    while ((c = getChar()) != '\n' )
    {
        if (c == BSPACE)
        {
            if (currentIdx > 0)
            {
                currentIdx--;
                putChar(BSPACE);
            }
        }
        else if (c != 0)
        {            
            if (currentIdx < BSIZE - 1)
            {
                if( (c == '-' && currentIdx != 0) || (pointFlag && c == '.') )  {
                    return -1;
                }
                if( (c <= '9' && c >= '0') || c == '.' || c == '-'){
                    putChar(c); 
                    if(c == '.')
                        pointFlag = 1;
                    auxBuffer[currentIdx++] = c;

                }
                else {
                    return -1;
                }
            }
        }
    }
    if(currentIdx == 0)
        return -1;
    putChar('\n');
    // ese ++ creo que no va, el ultimo
    auxBuffer[currentIdx++] = '\0';
    strcpy(dest, auxBuffer);
    return currentIdx;
}
//Copia del destino HASTA el punto
 int strcpyTilPoint(char *destination, const char *source)
 {
    int i = 0;
    while (*source != '\0' && *source!= '.')
    {
         *destination = *source;
         destination++;
         source++;
         i++;
    }

    *destination = '\0';
    return i;
 }

void stringToDouble(char * string, long double * num){
    char intPart[20];
    char doublePart[20]={0};

    int idxTilPoint = strcpyTilPoint(intPart, string);
    if(idxTilPoint != strlen(string)) {
        strcpy(doublePart, string + idxTilPoint + 1);
    }
    
    int ipart, dpart;

    ipart = strToInt(intPart);
    dpart = strToInt(doublePart);
    *num = ipart + (long double) dpart / pow(10, strlen(doublePart)); 
}

void printUser(char * name) {
    _write(name, 0x51AEAE);
}

void printError(char * err) {
    _write(err, 0xFF0000);
}