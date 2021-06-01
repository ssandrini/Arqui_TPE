#include <naiveConsole.h>

#define STD_OUT 0
#define STD_ERR 1
#define STD_COLOR 0xD
#define ERR_COLOR 0x47
#define WIDTH 80
#define HEIGHT 25 

/*
v1 _ _ _ _ _
 _ _ _ _ _ _
------------
v2 _ _ _ _ _
 _ _ _ _ _ _

*/
// static char buffer[64] = {'0'};
uint8_t * video1 = (uint8_t*)0xB8000;
uint8_t * video2 = (uint8_t*) (0xB8000 + WIDTH * 2 * (HEIGHT/2 +1));
uint8_t * currentVideo1 = (uint8_t*)0xB8000;
uint8_t * currentVideo2 = (uint8_t*) (0xB8000 + WIDTH *2* (HEIGHT/2 + 1));

int currentScreen = 0;

void changeScreen(int screen) {
	currentScreen = screen;
}

void drawLine() {
	uint8_t * l = video2 - WIDTH * 2;
	for(int i = 0; i < WIDTH; i++) {
		l[i * 2] = '-';
	}
}

void ncPrint(const char * string, int fd)
{
	int color = STD_COLOR;
	if(fd == STD_ERR)
		color = ERR_COLOR;
	for (int i = 0; string[i] != 0; i++)
		ncPrintChar(string[i], color);
}

void ncPrintChar(char character, int color)
{
	if(currentScreen == 0) {
		if(character == '\n')
			ncNewline();
		else if(character == -10){ // BACKSPACE (BORRAR)
			currentVideo1 -= 2;
			*currentVideo1 = ' ';
			*(currentVideo1 + 1) = color;
		}
		else { // CUALQUIER CARACTER
			*currentVideo1 = character;
			*(currentVideo1 + 1) = color;
			currentVideo1 += 2;
		}
		if(currentVideo1 ==  video2 - WIDTH * 2) {
		    scroll();
		}
	}
	else{
		if(character == '\n')
			ncNewline();
		else if(character == -10){
			currentVideo2 -= 2;
			*currentVideo2 = ' ';
			*(currentVideo2 + 1) = color;
		}
		else {
			*currentVideo2 = character;
			*(currentVideo2 + 1) = color;
			currentVideo2 += 2;
		}
		if(currentVideo2 ==  video2 + WIDTH * (HEIGHT - 1)) {
		    scroll();
		}
	}
	
}

void clearLine(uint8_t * p) {
	for(int i = 0; i < WIDTH; i++) {
		p[i * 2] = ' ';
	}
}


void ncNewline()
{
	if(currentScreen == 0) {
		do
		{
			ncPrintChar(' ', STD_OUT);
		}
		while((uint64_t)(currentVideo1 - video1) % (WIDTH*2) != 0);
	}
	else {
		do
		{
			ncPrintChar(' ', STD_OUT);
		}
		while((uint64_t)(currentVideo2 - video2) % (WIDTH*2) != 0);
	}
}

void ncClear()
{
	for (int i = 0; i < HEIGHT* WIDTH; i++)
		video1[i * 2] = ' ';
	currentVideo1 = video1;
	currentVideo2 = video2;
}

void scroll() {
	
	if(currentScreen == 0) {
		currentVideo1 = video1; //// lo llevo al principio
		uint8_t * aux = video1 + WIDTH * 2; // el aux apunta al principio de la sig linea
		while( aux < video2 - WIDTH * 2 ) { // copio en la linea de arriba 
			ncPrintChar(*aux, STD_COLOR);
			aux+=2;
		}
		aux -= WIDTH * 2;
		currentVideo1 = aux;
		clearLine(currentVideo1);
	}



	else{
		currentVideo2 = video2;
		uint8_t * aux = video2 + WIDTH * 2;
		while( aux < video2 + WIDTH * (HEIGHT-1)) {
			ncPrintChar(*aux, STD_COLOR);
			aux+=2;
		}
		aux -= WIDTH * 2;
		currentVideo2 = aux;
		clearLine(currentVideo2);
	}
}

// provisto por la catedra
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
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

void intToHexaStr(char * buff) {
	char auxStr[9] = "0x000000";
	int dim = 0;
	for (int i = 0; buff[i] != 0; i++) {
		dim++;
	}
	for (int j = 7; j >= 0 && dim != 0; j--) {
		auxStr[j] = buff[dim - 1];
		dim--;
	} 
	for (int k = 0; k < 8; k++) {
		buff[k] = auxStr[k];
	}
}