#pragma once
#include <SDL.h>
#include "Data.h"
#include <fstream>
using namespace std;
class ImageConverter
{
public:
	ImageConverter(char const* fileName);
	~ImageConverter();
	SDL_Surface* screen;
	int screenWidth;
	int screenHeight;
	int imageWidth;
	int imageHeight;
	SDL_Color grayScale[64];
	SDL_Color standardColors[64];
	SDL_Color dedicatedColors[64];
	SDL_Surface* bmp;
	int fileSize;
	fstream file;
	char const* title = "Image converter";
	void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
	void setPixel(int x, int y, SDL_Color C);
	SDL_Color getPixel(int x, int y);
	int byteRunCompress(Data *image);
	Data ByteRunDecompress(Data *image);
	Data standardColorAttachHeader(Data imageData);
	void loadBMP(char const* nazwa);
	void clearScreen();
	void fillArrays();
	void fillDedicatedColors();
	void changePalette(SDL_Color** pixmap);
};

