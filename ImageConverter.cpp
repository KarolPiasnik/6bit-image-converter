#include <iomanip>
#include <cmath>
#include "ImageConverter.h"
#include "HelperFunctions.h"
#include "Header.h"

ImageConverter::ImageConverter(const char * filename)
{
	loadBMP(filename);
	screen = SDL_SetVideoMode(imageWidth, imageHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (!bmp)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
	}
	else
	{
		SDL_Rect dstrect;
		dstrect.x = 0;
		dstrect.y = 0;
		SDL_BlitSurface(bmp, 0, screen, &dstrect);
		SDL_Flip(screen);
		SDL_FreeSurface(bmp);
	}

	if (!screen)
	{
		printf("Unable to set video: %s\n", SDL_GetError());
	}

	SDL_WM_SetCaption(title, NULL);
	fillArrays();
}

ImageConverter::~ImageConverter()
{
}

void ImageConverter::setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight))
	{
		/* Zamieniamy poszczególne skladowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

		/* Pobieramy informacji ile bajtów zajmuje jeden pixel */
		int bpp = screen->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

		/* Ustawiamy wartoœæ pixela, w zale¿noœci od formatu powierzchni*/
		switch (bpp)
		{
		case 1: //8-bit
			*p = pixel;
			break;

		case 2: //16-bit
			*(Uint16 *) p = pixel;
			break;

		case 3: //24-bit
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4: //32-bit
			*(Uint32 *) p = pixel;
			break;

		}
		/* update the screen (aka double buffering) */
	}
}

void ImageConverter::setPixel(int x, int y, SDL_Color C)
{
	this->setPixel(x, y, C.r, C.g, C.b);
}

SDL_Color ImageConverter::getPixel(int x, int y)
{
	SDL_Color color = {0, 0, 0};
	Uint32 col = 0;
	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight))
	{
		//determine position
		char* pPosition = (char*) screen->pixels;
		//offset by y
		pPosition += (screen->pitch*y);
		//offset by x
		pPosition += (screen->format->BytesPerPixel*x);
		//copy pixel data
		memcpy(&col, pPosition, screen->format->BytesPerPixel);
		//convert color
		SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
	}

	return (color);
}

void ImageConverter::byteRunCompress(Data * img)
{
	int i = 0;
	int d = 0;
	while (i < img->length)
	{
		if ((i < img->length - 2) &&
			(img->data[i] == img->data[i + 1]) &&
			(img->data[i] == img->data[i + 2]))
		{
			int j = 0;
			while ((i + j < img->length - 2) &&
				(img->data[i + j] == img->data[i + j + 1]) &&
				(img->data[i + j] == img->data[i + j + 2]) &&
				(j < 126))
			{
				j++;
			}
			img->data[d++] = -(j + 1);
			img->data[d++] = (int) img->data[i + j];
			i += (j + 2);
		}
		else
		{
			int j = 0;
			while ((i + j < img->length - 2) &&
				((img->data[i + j] != img->data[j + i + 1]) || (img->data[i + j] != img->data[j + i + 2])) &&
				(j < 128))
			{
				j++;
			}
			if ((i + j == img->length - 2) &&
				(j < 128))
			{
				j++;
			}
			if ((i + j == img->length - 1) &&
				(j < 128))
			{
				j++;
			}
			img->data[d++] = (j - 1);
			for (int k = 0; k < j; k++)
			{
				img->data[d++] = (int) img->data[i + k];
			}
			i += j;
		}
	}
	img->length = d;
}

void ImageConverter::byteRunDecompress(Data * img)
{
	int i = 0;
	vector <char> r;

	while (i < img->length)
	{
		if (img->data[i] == -128)
		{
			i++;
		}
		else if (img->data[i] < 0)
		{
			for (int j = 0; j < -(img->data[i] - 1); j++)
			{
				r.push_back((int) img->data[i + 1]);
			}
			i += 2;
		}
		else
		{
			for (int j = 0; j < (img->data[i] + 1); j++)
			{
				r.push_back((int) img->data[i + 1 + j]);
			}
			i += img->data[i] + 2;
		}
	}
	Data  res = Data(r);
	*img = res;
}

Data ImageConverter::predefinedTransform()
{
	SDL_Color pixel;
	uint8_t newPixel;
	Data result = Data(imageHeight*imageWidth);

	for (int i = 0; i < imageWidth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			pixel = getPixel(i, j);
			newPixel = 0;
			newPixel += (pixel.r / 64) << 4;
			newPixel += (pixel.g / 64) << 2;
			newPixel += (pixel.b / 64);
			setPixel(i, j, imposedPalette[newPixel]);
			result.data[i*imageHeight + j] = newPixel;

		}
	}
	SDL_Flip(screen);
	return result;
}

Data ImageConverter::dedicatedTransform()
{
	SDL_Color pixel;
	uint8_t newPixel;
	double minDistance;
	int closest;
	int distance;
	Data result = Data(imageHeight*imageWidth);
	for (int i = 0; i < imageWidth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			minDistance = 1000;
			closest = 65;
			distance = 0;
			pixel = getPixel(i, j);

			for (int k = 0; k < 64; ++k)
			{
				distance = sqrt(pow((dedicatedPalette[k].r - pixel.r)*0.3, 2) + pow((dedicatedPalette[k].g - pixel.g)*0.59, 2) + pow((dedicatedPalette[k].b - pixel.b)*0.11, 2));
				if (distance < minDistance)
				{
					closest = k;
					minDistance = distance;
				}

			}

			setPixel(i, j, dedicatedPalette[closest]);
			result.data[i*imageHeight + j] = closest;

		}
	}

	SDL_Flip(screen);
	return result;
}

Data ImageConverter::grayScaleTransform()
{
	double g;
	SDL_Color pixel;
	Data result = Data(imageHeight*imageWidth);

	for (int i = 0; i < imageWidth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			pixel = getPixel(i, j);
			g = 0.21*pixel.r + 0.72*pixel.g + 0.07* pixel.b;
			setPixel(i, j, grayScale[int(round(g)) / 4].r, grayScale[int(round(g)) / 4].g, grayScale[int(round(g)) / 4].b);
			result.data[i*imageHeight + j] = int(round(g)) / 4;
		}
	}
	SDL_Flip(screen);

	return result;
}

void ImageConverter::loadBMP(char const * filename)
{
	//clearScreen();
	bmp = SDL_LoadBMP(filename);
	screenWidth = imageWidth = bmp->w;
	screenHeight = imageHeight = bmp->h;
}

void ImageConverter::clearScreen()
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_Flip(screen);
}

void ImageConverter::saveToBmp(const char* name)
{
	SDL_SaveBMP(screen, name);
}

double ImageConverter::countDistance(const SDL_Color & firstColor, const SDL_Color & secondColor)
{
	double firstFraction = 0.299;
	double secondFraction = 0.587;
	double thirdFraction = 0.114;

	return pow((firstColor.r - secondColor.r) * firstFraction, 2)
		+ pow((firstColor.g - secondColor.g) * secondFraction, 2)
		+ pow((firstColor.b - secondColor.b) * thirdFraction, 2);
}

SDL_Color ImageConverter::findClosestPaletteColor(const SDL_Color & oldColor, char & paletteChoice)
{
	switch (paletteChoice)
	{
	case '1':
	{
		double closestDistance = countDistance(oldColor, imposedPalette[0]);
		SDL_Color bestColor = imposedPalette[0];

		for (int sentinel = 1; sentinel < 64; ++sentinel)
		{
			const double currentDistance = countDistance(oldColor, imposedPalette[sentinel]);

			if (currentDistance < closestDistance)
			{
				closestDistance = currentDistance;
				bestColor = imposedPalette[sentinel];
			}
		}

		return bestColor;
		break;
	}
	case '2':
	{
		double closestDistance = countDistance(oldColor, dedicatedPalette[0]);
		SDL_Color bestColor = dedicatedPalette[0];

		for (int sentinel = 1; sentinel < dedicatedPalette.size(); ++sentinel)
		{
			const double currentDistance = countDistance(oldColor, dedicatedPalette[sentinel]);

			if (currentDistance < closestDistance)
			{
				closestDistance = currentDistance;
				bestColor = dedicatedPalette[sentinel];
			}
		}

		return bestColor;
		break;
	}
	}
}

void ImageConverter::adjustRange(SDL_Color & currentColor, double & quantErrorR, double & quantErrorG, double & quantErrorB)
{
	if (currentColor.r + quantErrorR > 255)
	{
		currentColor.r = 255;
	}
	else if (currentColor.r + quantErrorR < 0)
	{
		currentColor.r = 0;
	}
	else
	{
		currentColor.r = currentColor.r + quantErrorR;
	}

	if (currentColor.g + quantErrorG > 255)
	{
		currentColor.g = 255;
	}
	else if (currentColor.g + quantErrorG < 0)
	{
		currentColor.g = 0;
	}
	else
	{
		currentColor.g = currentColor.g + quantErrorG;
	}

	if (currentColor.b + quantErrorB > 255)
	{
		currentColor.b = 255;
	}
	else if (currentColor.b + quantErrorB < 0)
	{
		currentColor.b = 0;
	}
	else
	{
		currentColor.b = currentColor.b + quantErrorB;
	}
}

void ImageConverter::dithering(SDL_Color ** inputImage, char & paletteChoice)
{
	double firstFraction = 7.0 / 16.0;
	double secondFraction = 3.0 / 16.0;
	double thirdFraction = 5.0 / 16.0;
	double fourthFraction = 1.0 / 16.0;

	// arrays of quantization error for all three RGB colors
	double ** quantErrorR = create_two_dimensional_array(imageWidth, imageHeight);
	double ** quantErrorG = create_two_dimensional_array(imageWidth, imageHeight);
	double ** quantErrorB = create_two_dimensional_array(imageWidth, imageHeight);

	fill_two_dimensional_array_with_value(quantErrorR, imageWidth, imageHeight, 0);
	fill_two_dimensional_array_with_value(quantErrorG, imageWidth, imageHeight, 0);
	fill_two_dimensional_array_with_value(quantErrorB, imageWidth, imageHeight, 0);

	for (int y = 0; y < imageHeight; ++y)
	{
		for (int x = 0; x < imageWidth; ++x)
		{
			SDL_Color oldColor = inputImage[x][y];
			SDL_Color currentColor = inputImage[x][y];

			// check whether new value has a proper range between 0 and 255 and adjust it if needed
			adjustRange(currentColor, quantErrorR[x][y], quantErrorG[x][y], quantErrorB[x][y]);

			const SDL_Color newColor = findClosestPaletteColor(currentColor, paletteChoice);

			// setPixel with newColor value (quantization error already added)
			setPixel(x, y, newColor);

			// calculate current quant error
			QuantError currentQuantError = {0, 0, 0};
			currentQuantError.r = oldColor.r - newColor.r;
			currentQuantError.g = oldColor.g - newColor.g;
			currentQuantError.b = oldColor.b - newColor.b;

			// add current quant error to neighbouring pixels
			if (x + 1 < imageWidth)
			{
				quantErrorR[x + 1][y] += currentQuantError.r * firstFraction;
				quantErrorG[x + 1][y] += currentQuantError.g * firstFraction;
				quantErrorB[x + 1][y] += currentQuantError.b * firstFraction;
			}

			if (y + 1 < imageHeight)
			{
				if (x - 1 >= 0)
				{
					quantErrorR[x - 1][y + 1] += currentQuantError.r * secondFraction;
					quantErrorG[x - 1][y + 1] += currentQuantError.g * secondFraction;
					quantErrorB[x - 1][y + 1] += currentQuantError.b * secondFraction;
				}

				quantErrorR[x][y + 1] += currentQuantError.r * thirdFraction;
				quantErrorG[x][y + 1] += currentQuantError.g * thirdFraction;
				quantErrorB[x][y + 1] += currentQuantError.b * thirdFraction;

				if (x + 1 < imageWidth)
				{
					quantErrorR[x + 1][y + 1] += currentQuantError.r * fourthFraction;
					quantErrorG[x + 1][y + 1] += currentQuantError.g * fourthFraction;
					quantErrorB[x + 1][y + 1] += currentQuantError.b * fourthFraction;
				}
			}
		}
	}

	delete_two_dimensional_array(quantErrorR, imageWidth);
	delete_two_dimensional_array(quantErrorG, imageWidth);
	delete_two_dimensional_array(quantErrorB, imageWidth);
}