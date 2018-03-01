#pragma once
#include <SDL.h>
#include <fstream> 
#include "Data.h"
#include "ImageConverter.h"

using namespace std;

class ImageConverter
{
public:
	ImageConverter(char const * filename);
	~ImageConverter();
	int screenWidth;
	int screenHeight;
	int imageWidth;
	int imageHeight;
	int fileSize;
	char const * title = "6-bit Image Converter";

	fstream file;
	SDL_Surface * screen;
	SDL_Surface * bmp;

	SDL_Color grayScale[64];
	SDL_Color imposedPalette[64];
	vector<SDL_Color> dedicatedPalette;

	SDL_Color getPixel(int x, int y);
	void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
	void setPixel(int x, int y, SDL_Color C);

	static void byteRunCompress(Data * image);
	static void byteRunDecompress(Data * image);

	Data predefinedTransform();
	Data dedicatedTransform();
	Data grayScaleTransform();

	void loadBMP(char const * filename);
	void saveToBmp(const char * name);
	void clearScreen();

	void fillArrays();
	void medianCut();
	void _medianCut(vector<SDL_Color>::iterator begin, vector<SDL_Color>::iterator end, int numberOfColors, int currentNumber);

	double countDistance(const SDL_Color & firstColor, const SDL_Color & secondColor);
	SDL_Color findClosestPaletteColor(const SDL_Color & currentColor, char & paletteChoice);
	void adjustRange(SDL_Color & currentColor, double & quantErrorR, double & quantErrorG, double & quantErrorB);
	void dithering(SDL_Color ** inputImage, char & paletteChoice);

	friend void copyCurrentSDLWindow(ImageConverter & converter, SDL_Color ** inputImage, int width, int height);
};