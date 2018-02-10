#include "HelperFunctions.h"

bool obtainFileStatus(const string & name)
{
	ifstream fin(name);
	return fin.good();
}

void validateFilename(string & name)
{
	system("cls");

	string firstExtension = "bmp";
	string secondExtension = "karol";
	int firstExtensionLength = firstExtension.length();
	int secondExtensionLength = secondExtension.length();

	cout << "- Now you will be asked to enter a name of a file to be processed. " << endl
		<< "- If there are two files sharing the same filename and one of them has .bmp and another .karol extension" << endl
		<< "  then the file with .bmp extension will be chosen." << endl
		<< "- If you want to override this behaviour you have to explicitly type filename with desired extension." << endl << endl
		<< "Please enter the name of the image to be processed: ";

	do
	{
		cin >> name;

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
	} while (cout << "Enter the proper name of the file!" << endl);

	cin.ignore(INT_MAX, '\n');
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

void displayFurtherInstructions()
{
	cout << "While having your SDL window active you can decide which operation will be performed." << endl
		<< "- To process another image press 'N' on your keyboard." << endl
		<< "- To end this program press 'ESC' on your keyboard." << endl;
}