#include <keyboard.h>
#include <./../include/naiveConsole.h>

#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define LEFT_CONTROL 0x1D
#define ESC 0x01
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_ALT 0x38
#define CAPSLOCK 0x3A
#define OFFSET 0x80

char shiftFlag = 0;
//IMPORTANTE, TENEMOS QUE ACLARAR EN EL INFORME EL TIPO DE TECLADO QUE ASUMIMOS
const char ascii_values[0x56][2] =
{
    {-1,-1},
    {0,0},
    {'1','!'},{'2','@'},{'3','#'},{'4','$'},{'5','$'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'=','+'},{0,0},
    {0,0},{'q','Q'},{'w','W'},{'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
    {0,0},
    {0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'},{';',':'},{'\'','\"'},
    {'`','~'},
    {0,0},
    {'\\','|'},
    {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'},{',','<'},{'.','>'},{'/','?'},{0,0},
    {0,0},{' ',' '},
    {0,0}
};

void keyboard_handler() 
{
    char key = _getKey();
    char ascii;
    switch (key)
    {
        case LEFT_SHIFT : case RIGHT_SHIFT :
            shiftFlag = 1;
            break;
        case (char)(LEFT_SHIFT+OFFSET) : case (char)(RIGHT_SHIFT+OFFSET) :
            shiftFlag=0;
            break;
        default:
            if(key < (char) 0x56) {
                ascii = getAscii(key);
                ncPrintChar(ascii);
            }
            break;
    }
    
    /*if(key == SHIFT ) {
        shiftFlag = 1;
    }
    else if(key == (char) (SHIFT+0x80)) {
        shiftFlag = 0;
    } 
    else {
        char ascii = getAscii(key);
        ncPrintChar(ascii);
    }
    */
    return;
    
}


char getAscii(unsigned int key) {
    if(shiftFlag)
        return ascii_values[key][1];
    else
        return ascii_values[key][0];
}