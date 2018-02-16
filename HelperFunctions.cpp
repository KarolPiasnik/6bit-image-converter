#include "HelperFunctions.h"
#include "ImageConverter.h"
#include "Header.h"

bool obtainFileStatus(const string & name)
{
	ifstream fin(name);
	return fin.good();
}

void validateFilename(string & name)
{
	string firstExtension = "bmp";
	string secondExtension = "karol";
	int firstExtensionLength = firstExtension.length();
	int secondExtensionLength = secondExtension.length();

	displayHint();
	displayInputRequest();

	do
	{
		getline(cin, name);

		// '.' not found
		if (name.find('.') == string::npos)
		{
			name.append(".").append(firstExtension);
			bool isFileExisiting = obtainFileStatus(name);

			if (isFileExisiting)
			{
				break;
			}
			else
			{
				name.erase(name.length() - firstExtensionLength);
				name.append(secondExtension);
				isFileExisiting = obtainFileStatus(name);

				if (isFileExisiting)
				{
					break;
				}
			}
		}
		else
		{
			bool isFileExisiting = obtainFileStatus(name);

			if (isFileExisiting)
			{
				break;
			}
		}

		displayHint();
		displayInputRequestOnFailure();
	} while (true);

	cout << endl;
}

void choosePalette(char & selection)
{
	cout << "Choose a color palette of the converted image." << endl;
	cout << "Please enter one of the following choices:" << endl;
	cout << "1) Predefined Color Palette       2) Algorithmically-chosen Color Palette" << endl;
	cout << "3) Grayscale" << endl;

	while (cin >> selection && selection != '1' && selection != '2' && selection != '3')
	{
		cout << "Please enter a number '1', '2' or '3': ";
		cin.ignore(INT_MAX, '\n');
	}

	cin.ignore(INT_MAX, '\n');
	cout << endl;
}

void chooseSaveOption(char & selection, bool & isAveragePredictorChosen)
{
	cout << "Choose an extension of this image which you want to convert to." << endl;
	cout << "Please enter one of the following choices:" << endl;
	cout << "1) .bmp                           2) .karol" << endl;
	cout << "3) don't save at all" << endl;

	while (cin >> selection && selection != '1' && selection != '2' && selection != '3')
	{
		cout << "Please enter a number '1', '2' or '3': ";
		cin.ignore(INT_MAX, '\n');
	}

	if (selection == '2')
	{
		char secondSelection;
		cout << endl << "Choose whether you want an Average Predictor to be used." << endl;
		cout << "Please enter one of the following choices:" << endl;
		cout << "1) yes                        2) no" << endl;

		while (cin >> secondSelection && secondSelection != '1' && secondSelection != '2')
		{
			cout << "Please enter a number '1' or '2'";
			cin.ignore(INT_MAX, '\n');
		}

		if (secondSelection == '1')
		{
			isAveragePredictorChosen = true;
		}
	}

	cin.ignore(INT_MAX, '\n');
	cout << endl;
}

void chooseDithering(bool & isDitheringChosen)
{
	char selection;

	cout << "Choose whether you want a Dithering to be used." << endl;
	cout << "Please enter one of the following choices:" << endl;
	cout << "1) yes                        2) no" << endl;

	while (cin >> selection && selection != '1' && selection != '2')
	{
		cout << "Please enter a number '1' or '2'";
		cin.ignore(INT_MAX, '\n');
	}

	if (selection == '1')
	{
		isDitheringChosen = true;
	}

	cin.ignore(INT_MAX, '\n');
	cout << endl;
}

void displayHint()
{
	system("cls");

	cout << "- Now you will be asked to enter a name of a file to be processed. " << endl
		<< "- If there are two files sharing the same filename and one of them has .bmp and another .karol extension" << endl
		<< "  then the file with .bmp extension will be chosen." << endl
		<< "- If you want to override this behaviour you have to explicitly type filename with desired extension." << endl << endl;
}

void displayInputRequest()
{
	cout << "Please enter the name of the image to be processed: ";
}

void displayInputRequestOnFailure()
{
	cout << "Enter the proper name of the file!" << endl;
}

void displayFurtherInstructions()
{
	cout << "While having your SDL window active you can decide which operation will be performed." << endl
		<< "- To process another image press 'N' on your keyboard." << endl
		<< "- To end this program press 'ESC' on your keyboard." << endl;
}


double ** create_two_dimensional_array(int rows, int columns)
{
	double ** array = nullptr;

	try
	{
		array = new double *[rows];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		cout << ba.what() << endl;							//	displays the exact cause
	}

	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		try
		{
			*(array + sentinel) = new double[columns];
		}

		catch (bad_alloc & ba)
		{
			cout << "Error! (couldn't allocate the dynamic array)" << endl;
			cout << ba.what() << endl;						//	displays the exact cause
		}

	}

	return array;
}

SDL_Color ** create_two_dimensional_SDL_array(int rows, int columns)
{
	SDL_Color ** array = nullptr;

	try
	{
		array = new SDL_Color *[rows];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		cout << ba.what() << endl;							//	displays the exact cause
	}

	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		try
		{
			*(array + sentinel) = new SDL_Color[columns];
		}

		catch (bad_alloc & ba)
		{
			cout << "Error! (couldn't allocate the dynamic array)" << endl;
			cout << ba.what() << endl;						//	displays the exact cause
		}

	}

	return array;
}

void fill_two_dimensional_array_with_value(double ** array, int rows, int columns, int value)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			array[sentinel][secondSentinel] = value;
		}
	}
}

void delete_two_dimensional_array(double ** array, int columns)
{
	for (int sentinel = 0; sentinel < columns; ++sentinel)
	{
		delete[] array[sentinel];
	}

	delete[] array;
}

void display_two_dimensional_array_rows_in_single_line_negative_numbers(double ** array, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			cout.precision(2);
			cout << fixed << array[sentinel][secondSentinel] << " ";
		}

		cout << endl;
	}
}

void copyCurrentSDLWindow(ImageConverter & converter, SDL_Color ** inputImage, int width, int height)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			inputImage[x][y] = converter.getPixel(x, y);
		}
	}
}