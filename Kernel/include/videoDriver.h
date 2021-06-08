#ifndef __VIDEO_DRIVER_H_
#define __VIDEO_DRIVER_H_
#include <font8x16.h>
#include <stdint.h>

#define WIDTH 1024
#define HEIGHT 768
#define LETTER_WIDTH 8
#define LETTER_HEIGHT 16
#define BACKGROUND_COLOR 0x000000


char * getDataPosition(int x, int y);
char positionEmpty(int x, int y);
int getPixelColor(int x, int y);
void writePixel(int x, int y, int rgb_hexa);
void drawLine(int y);
void writeLetter(int key, int posX, int posY, int letter_color);
void clearLine(int y_initial);
void setSegmentBlank(int x_initial, int x_final, int y_initial, int y_final, int background_color);
#endif