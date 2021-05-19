#include <keyboard.h>
#include <./../include/naiveConsole.h>

#define BACKSPACE 255
#define SHIFT 0x2A
char shiftFlag = 0;
//IMPORTANTE, TENEMOS QUE ACLARAR EN EL INFORME EL TIPO DE TECLADO QUE ASUMIMOS
const char ascii_values[0x56][2] =
{
    {-1,-1},
    {231,231},
    {'1','!'},{'2','@'},{'3','#'},{'4','$'},{'5','$'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'=','+'},{'BACKSPACE', 'BAKSPACE'},
    {'TAB','TAB'},{'q','Q'},{'w','W'},{'e','E'},{'r','R'},{'t,T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
    {'ENTER','ENTER'},
    {'LCTRL','LCTRL'},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'},{';',':'},{'\'','\"'},
    {'\\','|'},
    {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'},{',','<'},{'.','>'},{'/','?'},{'RIGHTSHIFT','RIGHTSHIFT'},
    {'LEFTALT','LEFTALT'},{' ',' '},
    {'CAPSLOCK', 'CAPSLOCK'},
    // falta terminar
};

void keyboard_handler() 
{
    char key = _getKey();
    if(key == SHIFT ) {
        shiftFlag = 1;
    }
    else if(key == (char) (SHIFT+0x80)) {
        shiftFlag = 0;
    } 
    else {
        char ascii = getAscii(key);
        ncPrintChar(ascii);
    }
    return;
}



char getAscii(unsigned int key) {

    if(shiftFlag)
        return ascii_values[key][1];
    else
        return ascii_values[key][0];

}