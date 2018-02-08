﻿#include "ImageConverter.h"
#include "Header.h"


ImageConverter::ImageConverter(const char* fileName)
{
	loadBMP(fileName);
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
	if ((x >= 0) && (x<screenWidth) && (y >= 0) && (y<screenHeight))
	{
		/* Zamieniamy poszczególne skladowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

		/* Pobieramy informacji ile bajtów zajmuje jeden pixel */
		int bpp = screen->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

		/* Ustawiamy wartoœæ pixela, w zale¿noœci od formatu powierzchni*/
		switch (bpp)
		{
		case 1: //8-bit
			*p = pixel;
			break;

		case 2: //16-bit
			*(Uint16 *)p = pixel;
			break;

		case 3: //24-bit
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4: //32-bit
			*(Uint32 *)p = pixel;
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
	SDL_Color color;
	Uint32 col = 0;
	if ((x >= 0) && (x<screenWidth) && (y >= 0) && (y<screenHeight)) {
		//determine position
		char* pPosition = (char*)screen->pixels;
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

int ImageConverter::byteRunCompress(Data * img)
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
			img->data[d++] = (int)img->data[i + j];
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
			for (int k = 0; k<j; k++)
			{
				img->data[d++] = (int)img->data[i + k];
			}
			i += j;
		}
	}
	return d;
}

Data ImageConverter::ByteRunDecompress(Data * img)
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
			for (int j = 0; j<-(img->data[i] - 1); j++)
			{
				r.push_back((int)img->data[i + 1]);
			}
			i += 2;
		}
		else
		{
			for (int j = 0; j<(img->data[i] + 1); j++)
			{
				r.push_back((int)img->data[i + 1 + j]);
			}
			i += img->data[i] + 2;
		}
	}
	Data res(r);
	return res;
}

Data ImageConverter::standardColorAttachHeader(Data imageData)
{
	Header header = Header();
	header.setType(0);
	header.setFileSize(imageData.length + 17);
	header.setBeginning(17);
	header.setImageSize(imageWidth, imageHeight);
	header.setColorSet(0);

	return header.byteData += imageData;
}

void ImageConverter::loadBMP(char const * nazwa)
{
	//clearScreen();
	bmp = SDL_LoadBMP(nazwa);
	screenWidth = imageWidth = bmp->w;
	screenHeight = imageHeight = bmp->h;
}

void ImageConverter::clearScreen()
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_Flip(screen);
}

/*
Data standard(string name, bool compress) {
    std::ofstream myFile(name.c_str(),  std::ofstream::binary);
    Header header = Header();
    header.setFileSize((imageWidth*imageHeight*3)/4+1+17);
    header.setBeginning(17);
    header.setColorSet(0);
    header.setType(42);
    header.setImageSize(imageWidth,imageHeight);
    myFile.write(&header.byteData.data[0], header.byteData.length);


    uint8_t * imageData = new uint8_t[imageWidth*imageHeight];
    for(int i = 0; i<imageWidth*imageHeight; ++i){
        imageData[i]=0;
    }

    int byteCounter = 0;
    int bitCounter = 0;
    int newPixel = 0;

    for(int i = 0; i<imageWidth; ++i){
        for(int j = 0; j<imageHeight; ++j){
            SDL_Color pixel = getPixel(i,j);
            newPixel = 0;

            if(bitCounter==8)
            {
                bitCounter = 0;
                ++byteCounter;
            }

            imageData[byteCounter] += (pixel.r /64)<<(6-bitCounter);
            newPixel += (pixel.r /64)<<4;
            bitCounter += 2;

            if(bitCounter==8)
            {
                bitCounter = 0;
                ++byteCounter;
            }

            imageData[byteCounter] += (pixel.g /64)<<(6-bitCounter);
            newPixel += (pixel.g /64)<<2;
            bitCounter += 2;

            if(bitCounter==8)
            {
                bitCounter = 0;
                ++byteCounter;
            }

            imageData[byteCounter] += (pixel.b /64)<<(6-bitCounter);
            newPixel += (pixel.b /64);
            bitCounter += 2;

            setPixel(i,j,standardColors[newPixel].r,standardColors[newPixel].g,standardColors[newPixel].b);

        }
    }

    Data result = Data(byteCounter);
    for(int i = 0; i < byteCounter; ++i){
        result.data[i] = imageData[i];
    }

    if(compress)
        cout<<"Rozmiar po kompresji: "<<byteRunCompress(&result)<<endl;

    myFile.write(&result.data[0], result.length);
    myFile.close();

    SDL_Flip(screen);

    return result;
}
*/