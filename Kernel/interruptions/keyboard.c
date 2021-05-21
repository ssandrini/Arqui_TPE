#include <keyboard.h>
#include <naiveConsole.h>
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define LEFT_CONTROL 0x1D
#define ESC 0x01
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_ALT 0x38
#define CAPSLOCK 0x3A
#define OFFSET 0x80
#define BUFFER_SIZE 512
unsigned char shiftFlag = 0;
unsigned char ctrlFlag = 0;
unsigned char buffer[BUFFER_SIZE]={0};
unsigned int buffIndex = 0;
//IMPORTANTE, TENEMOS QUE ACLARAR EN EL INFORME EL TIPO DE TECLADO QUE ASUMIMOS
const char ascii_values[0x56][2] =
{
    {-1,-1},
    {0,0},
    {'1','!'},{'2','@'},{'3','#'},{'4','$'},{'5','$'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'=','+'},{0,0},
    {0,0},{'q','Q'},{'w','W'},{'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
    {'\n','\n'},
    {0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'},{';',':'},{'\'','\"'},
    {'`','~'},
    {0,0},
    {'\\','|'},
    {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'},{',','<'},{'.','>'},{'/','?'},{0,0},
    {0,0},{0,0},{' ',' '},
    {0,0}
};

void keyboard_handler() 
{
    unsigned char key = _getKey();
    switch (key)
    {
        case LEFT_SHIFT : case RIGHT_SHIFT :
            shiftFlag = 1;
            break;
        case LEFT_SHIFT + OFFSET : case RIGHT_SHIFT + OFFSET :
            shiftFlag = 0;
            break;
        default:
            if(key < 0x56) {
                
                buffer[buffIndex++] = getAscii(key);
                buffer[buffIndex] = 0;
                // ncPrintChar(getAscii(key), 13);
            }
            break;
    }
    return;
}

char getAscii(unsigned int key) {
    if(shiftFlag)
        return ascii_values[key][1];
    else
        return ascii_values[key][0];
}

void removeBuffer() {
    buffer[0] = 0;
    buffIndex = 0;
}

unsigned char * getBuffer() {
    return buffer;
}

unsigned int getBufferSize() {
    return buffIndex;
}

// >> ingrese su nombre:
//  flor
// >> bienvenida flor
// >> aasdasjkldas
