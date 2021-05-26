#include <naiveConsole.h>

#define STD_OUT 0
#define STD_ERR 1
#define STD_COLOR 0xD
#define ERR_COLOR 0x47

// static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
// static char buffer[64] = {'0'};
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

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
	if(currentVideo ==  video + width * 2 * height) {
		scroll();
	}
	if(character == '\n')
		ncNewline();
	else {
		*currentVideo = character;
		*(currentVideo + 1) = color;
		currentVideo += 2;
	}
}

void clearLine(uint8_t * p) {
	for(int i = 0; i < width; i++) {
		p[i * 2] = ' ';
	}
}


void ncNewline()
{
	do
	{
		ncPrintChar(' ', STD_OUT);
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

void scroll() {
	currentVideo = video;
	uint8_t * aux = video + width * 2;
	while( aux < video + width * 2 * height) {
		ncPrintChar(*aux, STD_COLOR);
		aux+=2;
	}
	aux -= width * 2;
	currentVideo = aux;
	clearLine(currentVideo);
}
