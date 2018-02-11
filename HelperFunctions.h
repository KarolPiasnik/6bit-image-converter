#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>

using namespace std;

bool obtainFileStatus(const string &);
void validateFilename(string &);

void choosePalette(char &);
void chooseSaveOption(char &, bool &);

void displayHint();
void displayInputRequest();
void displayInputRequestOnFailure();
void displayFurtherInstructions();