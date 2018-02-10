#include "ImageConverter.h"
#include <algorithm>
#include <iostream>


void ImageConverter::_medianCut(vector<SDL_Color> pixels, int numberOfColors = 64, int currentNumber = 1)
{
	if (numberOfColors == currentNumber) 
	{
		long int sumr = 0;
		long int sumg = 0;
		long int sumb = 0;

		for (int i = 0; i < pixels.size(); ++i)
		{
			sumr += pixels[i].r;
			sumg += pixels[i].g;
			sumb += pixels[i].b;
		}

		SDL_Color resultColor;
		resultColor.r = sumr / pixels.size();
		resultColor.g = sumg / pixels.size();
		resultColor.b = sumb / pixels.size();
		dedicated.push_back(resultColor);


			
		

	}
	else 
	{
		vector<SDL_Color> pixelsUpper;
		vector<SDL_Color> pixelsLower;
		for (int i = 0; i < pixels.size(); ++i)
		{
			if (i < pixels.size() / 2)
				pixelsUpper.push_back(pixels[i]);
			else
				pixelsLower.push_back(pixels[i]);

		}

		_medianCut(pixelsLower, numberOfColors, currentNumber * 2);
		_medianCut(pixelsUpper, numberOfColors, currentNumber * 2);

	}
	
}

void ImageConverter::medianCut() 
{
	int maxr = 0 , maxg = 0, maxb = 0, minr = 255, ming = 255, minb = 255;
	vector<SDL_Color> pixels = {};
	SDL_Color pixel;
	for (int i = 0; i < imageWidth; ++i) { //getting minimums, maximums a all pixels
		for (int j = 0; j < imageHeight; ++j) {
			pixel = getPixel(i, j);
			if (maxr < pixel.r)
				maxr = pixel.r;
			if (maxb < pixel.b)
				maxb = pixel.b;
			if (maxg < pixel.g)
				maxg = pixel.g;
			if (minr > pixel.r)
				minr = pixel.r;
			if (ming > pixel.g)
				ming = pixel.g;
			if (maxb > pixel.b)
				minb = pixel.b;
			pixels.push_back(pixel);
		}
	}

	char order; //chosing by which color value sort

	if (maxb - minb > maxg - ming && maxb - minb > maxr - minr) {
		order = 'b';
	}
	else if (maxr - minr > maxg - ming && maxr - minr > maxb - minb) {
		order = 'r';
	}
	else  {
		order = 'g';
	}

	switch (order) 
	{
	case 'r':
		std::sort(pixels.begin(), pixels.end(), [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	case 'g':
		std::sort(pixels.begin(), pixels.end(), [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	case 'b':
		std::sort(pixels.begin(), pixels.end(), [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	}

	_medianCut(pixels);

	switch (order)
	{
	case 'r':
		std::sort(dedicated.begin(), dedicated.end(), [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	case 'g':
		std::sort(dedicated.begin(), dedicated.end(), [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	case 'b':
		std::sort(dedicated.begin(), dedicated.end(), [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	}
	
	for (int i = 0; i < dedicated.size(); ++i)
		cout << +dedicated[i].r << " " << +dedicated[i].g << " " << +dedicated[i].b << endl;
	
}




void ImageConverter::fillArrays()
{
	grayScale[0] = { 0,0,0 };
	grayScale[1] = { 4,4,4 };
	grayScale[2] = { 8,8,8 };
	grayScale[3] = { 12,12,12 };
	grayScale[4] = { 16,16,16 };
	grayScale[5] = { 20,20,20 };
	grayScale[6] = { 24,24,24 };
	grayScale[7] = { 28,28,28 };
	grayScale[8] = { 32,32,32 };
	grayScale[9] = { 36,36,36 };
	grayScale[10] = { 40,40,40 };
	grayScale[11] = { 45,45,45 };
	grayScale[12] = { 49,49,49 };
	grayScale[13] = { 53,53,53 };
	grayScale[14] = { 57,57,57 };
	grayScale[15] = { 61,61,61 };
	grayScale[16] = { 65,65,65 };
	grayScale[17] = { 69,69,69 };
	grayScale[18] = { 73,73,73 };
	grayScale[19] = { 77,77,77 };
	grayScale[20] = { 81,81,81 };
	grayScale[21] = { 85,85,85 };
	grayScale[22] = { 89,89,89 };
	grayScale[23] = { 93,93,93 };
	grayScale[24] = { 97,97,97 };
	grayScale[25] = { 101,101,101 };
	grayScale[26] = { 105,105,105 };
	grayScale[27] = { 109,109,109 };
	grayScale[28] = { 113,113,113 };
	grayScale[29] = { 117,117,117 };
	grayScale[30] = { 121,121,121 };
	grayScale[31] = { 125,125,125 };
	grayScale[32] = { 130,130,130 };
	grayScale[33] = { 134,134,134 };
	grayScale[34] = { 138,138,138 };
	grayScale[35] = { 142,142,142 };
	grayScale[36] = { 146,146,146 };
	grayScale[37] = { 150,150,150 };
	grayScale[38] = { 154,154,154 };
	grayScale[39] = { 158,158,158 };
	grayScale[40] = { 162,162,162 };
	grayScale[41] = { 166,166,166 };
	grayScale[42] = { 170,170,170 };
	grayScale[43] = { 174,174,174 };
	grayScale[44] = { 178,178,178 };
	grayScale[45] = { 182,182,182 };
	grayScale[46] = { 186,186,186 };
	grayScale[47] = { 190,190,190 };
	grayScale[48] = { 194,194,194 };
	grayScale[49] = { 198,198,198 };
	grayScale[50] = { 202,202,202 };
	grayScale[51] = { 206,206,206 };
	grayScale[52] = { 210,210,210 };
	grayScale[53] = { 215,215,215 };
	grayScale[54] = { 219,219,219 };
	grayScale[55] = { 223,223,223 };
	grayScale[56] = { 227,227,227 };
	grayScale[57] = { 231,231,231 };
	grayScale[58] = { 235,235,235 };
	grayScale[59] = { 239,239,239 };
	grayScale[60] = { 243,243,243 };
	grayScale[61] = { 247,247,247 };
	grayScale[62] = { 251,251,251 };
	grayScale[63] = { 255,255,255 };

	predefined[0] = { 0,0,0 };
	predefined[1] = { 0,0,84 };
	predefined[2] = { 0,0,168 };
	predefined[3] = { 0,0,252 };
	predefined[4] = { 0,84,0 };
	predefined[5] = { 0,84,84 };
	predefined[6] = { 0,84,168 };
	predefined[7] = { 0,84,252 };
	predefined[8] = { 0,168,0 };
	predefined[9] = { 0,168,84 };
	predefined[10] = { 0,168,168 };
	predefined[11] = { 0,168,252 };
	predefined[12] = { 0,252,0 };
	predefined[13] = { 0,252,84 };
	predefined[14] = { 0,252,168 };
	predefined[15] = { 0,252,252 };
	predefined[16] = { 84,0,0 };
	predefined[17] = { 84,0,84 };
	predefined[18] = { 84,0,168 };
	predefined[19] = { 84,0,252 };
	predefined[20] = { 84,84,0 };
	predefined[21] = { 84,84,84 };
	predefined[22] = { 84,84,168 };
	predefined[23] = { 84,84,252 };
	predefined[24] = { 84,168,0 };
	predefined[25] = { 84,168,84 };
	predefined[26] = { 84,168,168 };
	predefined[27] = { 84,168,252 };
	predefined[28] = { 84,252,0 };
	predefined[29] = { 84,252,84 };
	predefined[30] = { 84,252,168 };
	predefined[31] = { 84,252,252 };
	predefined[32] = { 168,0,0 };
	predefined[33] = { 168,0,84 };
	predefined[34] = { 168,0,168 };
	predefined[35] = { 168,0,252 };
	predefined[36] = { 168,84,0 };
	predefined[37] = { 168,84,84 };
	predefined[38] = { 168,84,168 };
	predefined[39] = { 168,84,252 };
	predefined[40] = { 168,168,0 };
	predefined[41] = { 168,168,84 };
	predefined[42] = { 168,168,168 };
	predefined[43] = { 168,168,252 };
	predefined[44] = { 168,252,0 };
	predefined[45] = { 168,252,84 };
	predefined[46] = { 168,252,168 };
	predefined[47] = { 168,252,252 };
	predefined[48] = { 252,0,0 };
	predefined[49] = { 252,0,84 };
	predefined[50] = { 252,0,168 };
	predefined[51] = { 252,0,252 };
	predefined[52] = { 252,84,0 };
	predefined[53] = { 252,84,84 };
	predefined[54] = { 252,84,168 };
	predefined[55] = { 252,84,252 };
	predefined[56] = { 252,168,0 };
	predefined[57] = { 252,168,84 };
	predefined[58] = { 252,168,168 };
	predefined[59] = { 252,168,252 };
	predefined[60] = { 252,252,0 };
	predefined[61] = { 252,252,84 };
	predefined[62] = { 252,252,168 };
	predefined[63] = { 252,252,252 };

	medianCut();
}




