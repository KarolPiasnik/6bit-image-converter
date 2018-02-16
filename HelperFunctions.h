#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <SDL.h>
#include "ImageConverter.h"

using namespace std;

struct QuantError
{
	double r;
	double g;
	double b;
};

bool obtainFileStatus(const string &);
void validateFilename(string &);

void choosePalette(char &);
void chooseSaveOption(char &, bool &);
void chooseDithering(bool &);

void displayHint();
void displayInputRequest();
void displayInputRequestOnFailure();
void displayFurtherInstructions();

double ** create_two_dimensional_array(int, int);
SDL_Color ** create_two_dimensional_SDL_array(int, int);
void delete_two_dimensional_array(double **, int);
void fill_two_dimensional_array_with_value(double **, int, int, int);
void display_two_dimensional_array_rows_in_single_line_negative_numbers(double **, int, int);
void copyCurrentSDLWindow(ImageConverter & converter, SDL_Color ** inputImage, int width, int height);