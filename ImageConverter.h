#pragma once
#include <SDL.h>
#include "Data.h"
#include <fstream>

using namespace std;

class ImageConverter
{
public:
	ImageConverter(char const * filename);
	~ImageConverter();
	SDL_Surface * screen;
	int screenWidth;
	int screenHeight;
	int imageWidth;
	int imageHeight;
	SDL_Color grayScale[64];
	SDL_Color predefined[64];
	vector<SDL_Color> dedicated;
	SDL_Surface * bmp;
	int fileSize;
	fstream file;
	char const * title = "6-bit Image Converter";
	void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
	void setPixel(int x, int y, SDL_Color C);
	SDL_Color getPixel(int x, int y);
	static void byteRunCompress(Data * image);
	static void byteRunDecompress(Data * image);
	void predefinedTransform();
	void dedicatedTransform();
	void grayScaleTransform();
	void loadBMP(char const * filename);
	void clearScreen();
	void fillArrays();
	void medianCut();
	void _medianCut(vector<SDL_Color> pixels, int numberOfColors, int currentNumber);
};