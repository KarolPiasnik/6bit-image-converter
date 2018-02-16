#include "ImageConverter.h"
#include <algorithm>
#include <iostream>


void ImageConverter::_medianCut(vector<SDL_Color>::iterator start, vector<SDL_Color>::iterator end, int numberOfColors = 64, int currentNumber = 1)
{	
	int size = end - start;
	vector<SDL_Color>::iterator current = start;
	int maxr = 0, maxg = 0, maxb = 0, minr = 255, ming = 255, minb = 255;
	for (vector<SDL_Color>::iterator tmp = start; tmp < end; ++tmp) 
	{
		if (maxr < tmp->r)
			maxr = tmp->r;
		if (maxb < tmp->b)
			maxb = tmp->b;
		if (maxg < tmp->g)
			maxg = tmp->g;
		if (minr > tmp->r)
			minr = tmp->r;
		if (ming > tmp->g)
			ming = tmp->g;
		if (minb > tmp->b)
			minb = tmp->b;
	}

	char order; //chosing by which color value sort

	if (maxb - minb > maxg - ming && maxb - minb > maxr - minr) {
		order = 'b';
	}
	else if (maxr - minr > maxg - ming && maxr - minr > maxb - minb) {
		order = 'r';
	}
	else {
		order = 'g';
	}

	switch (order)
	{
	case 'r':
		std::sort(start, end, [](const SDL_Color &x, const SDL_Color &y) { return (x.r < y.r); });
		break;
	case 'g':
		std::sort(start, end, [](const SDL_Color &x, const SDL_Color &y) { return (x.g < y.g); });
		break;
	case 'b':
		std::sort(start, end, [](const SDL_Color &x, const SDL_Color &y) { return (x.b < y.b); });
		break;
	}

	if (numberOfColors == currentNumber) 
	{
		long int sumr = 0;
		long int sumg = 0;
		long int sumb = 0;

		for (int i = 0; current != end; ++current)
		{
			sumr += current->r;
			sumg += current->g;
			sumb += current->b;
		}

		SDL_Color resultColor;
		resultColor.r = sumr / size;
		resultColor.g = sumg / size;
		resultColor.b = sumb / size;
		dedicatedPalette.push_back(resultColor);

	}
	else 
	{
		
		_medianCut(start,start+size/2, numberOfColors, currentNumber * 2);
		_medianCut(start + size / 2 + 1, end, numberOfColors, currentNumber * 2);

	}
	
}

void ImageConverter::medianCut() 
{
	vector<SDL_Color> pixels = {};
	SDL_Color pixel;
	for (int i = 0; i < imageWidth; ++i) { //getting minimums, maximums a all pixels
		for (int j = 0; j < imageHeight; ++j) {			
			pixels.push_back(getPixel(i,j));
		}
	}

	_medianCut(pixels.begin(), pixels.end());
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

	imposedPalette[0] = { 0,0,0 };
	imposedPalette[1] = { 0,0,84 };
	imposedPalette[2] = { 0,0,168 };
	imposedPalette[3] = { 0,0,252 };
	imposedPalette[4] = { 0,84,0 };
	imposedPalette[5] = { 0,84,84 };
	imposedPalette[6] = { 0,84,168 };
	imposedPalette[7] = { 0,84,252 };
	imposedPalette[8] = { 0,168,0 };
	imposedPalette[9] = { 0,168,84 };
	imposedPalette[10] = { 0,168,168 };
	imposedPalette[11] = { 0,168,252 };
	imposedPalette[12] = { 0,252,0 };
	imposedPalette[13] = { 0,252,84 };
	imposedPalette[14] = { 0,252,168 };
	imposedPalette[15] = { 0,252,252 };
	imposedPalette[16] = { 84,0,0 };
	imposedPalette[17] = { 84,0,84 };
	imposedPalette[18] = { 84,0,168 };
	imposedPalette[19] = { 84,0,252 };
	imposedPalette[20] = { 84,84,0 };
	imposedPalette[21] = { 84,84,84 };
	imposedPalette[22] = { 84,84,168 };
	imposedPalette[23] = { 84,84,252 };
	imposedPalette[24] = { 84,168,0 };
	imposedPalette[25] = { 84,168,84 };
	imposedPalette[26] = { 84,168,168 };
	imposedPalette[27] = { 84,168,252 };
	imposedPalette[28] = { 84,252,0 };
	imposedPalette[29] = { 84,252,84 };
	imposedPalette[30] = { 84,252,168 };
	imposedPalette[31] = { 84,252,252 };
	imposedPalette[32] = { 168,0,0 };
	imposedPalette[33] = { 168,0,84 };
	imposedPalette[34] = { 168,0,168 };
	imposedPalette[35] = { 168,0,252 };
	imposedPalette[36] = { 168,84,0 };
	imposedPalette[37] = { 168,84,84 };
	imposedPalette[38] = { 168,84,168 };
	imposedPalette[39] = { 168,84,252 };
	imposedPalette[40] = { 168,168,0 };
	imposedPalette[41] = { 168,168,84 };
	imposedPalette[42] = { 168,168,168 };
	imposedPalette[43] = { 168,168,252 };
	imposedPalette[44] = { 168,252,0 };
	imposedPalette[45] = { 168,252,84 };
	imposedPalette[46] = { 168,252,168 };
	imposedPalette[47] = { 168,252,252 };
	imposedPalette[48] = { 252,0,0 };
	imposedPalette[49] = { 252,0,84 };
	imposedPalette[50] = { 252,0,168 };
	imposedPalette[51] = { 252,0,252 };
	imposedPalette[52] = { 252,84,0 };
	imposedPalette[53] = { 252,84,84 };
	imposedPalette[54] = { 252,84,168 };
	imposedPalette[55] = { 252,84,252 };
	imposedPalette[56] = { 252,168,0 };
	imposedPalette[57] = { 252,168,84 };
	imposedPalette[58] = { 252,168,168 };
	imposedPalette[59] = { 252,168,252 };
	imposedPalette[60] = { 252,252,0 };
	imposedPalette[61] = { 252,252,84 };
	imposedPalette[62] = { 252,252,168 };
	imposedPalette[63] = { 252,252,252 };

	medianCut();
	
}




