#include <naiveConsole.h>

#define STD_OUT 0
#define STD_ERR 1
#define STD_COLOR 0xD
#define ERR_COLOR 0x47
#define WIDTH 80
#define HEIGHT 25 

/*
p------------------------------
------------------------------x //WIDTH * HEIGHT - 2
x.............................. height/2
v------------------------------
-------------------------------
*/

// static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
// static char buffer[64] = {'0'};
uint8_t * video1 = (uint8_t*)0xB8000;
uint8_t * video2 = (uint8_t*) (0xB8000 + WIDTH * 2 * (HEIGHT/2 +1));
uint8_t * currentVideo1 = (uint8_t*)0xB8000;
uint8_t * currentVideo2 = (uint8_t*) (0xB8000 + WIDTH *2* (HEIGHT/2 + 1));

int currentScreen = 0;

void changeScreen(int screen) {
	currentScreen = screen;
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
		if(currentVideo1 ==  video1 + WIDTH * HEIGHT ) {
		    scroll();
		}
		if(character == '\n')
			ncNewline();
		else if(character == -10){
			currentVideo1 -= 2;
			*currentVideo1 = ' ';
			*(currentVideo1 + 1) = color;
		}
		else {
			*currentVideo1 = character;
			*(currentVideo1 + 1) = color;
			currentVideo1 += 2;
		}
	}
	else{
		if(currentVideo2 ==  video2 + WIDTH *2* (HEIGHT/2 + 1)) {
		    scroll();
		}
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
	
	if(currentScreen == 0){
		currentVideo1 = video1; //// primer linea
		uint8_t * aux = video1 + WIDTH * 2;
		while( aux < video1 + WIDTH * HEIGHT ) {
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
		while( aux < video2 + WIDTH * HEIGHT) {
			ncPrintChar(*aux, STD_COLOR);
			aux+=2;
		}
		aux -= WIDTH * 2;
		currentVideo2 = aux;
		clearLine(currentVideo2);
	}
}
