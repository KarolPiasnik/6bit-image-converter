#pragma once
#include <iostream>
#include "Data.h"

using namespace std;

class Header
{
public:
	Header();
	~Header();
	Data byteData = Data(17);

	void setType(int type)
	{
		byteData.data[0] = type >> 8;
		byteData.data[1] = (type << 24) >> 24;
	}

	void setFileSize(int fileSize)
	{

		byteData.data[2] = fileSize >> 24;
		byteData.data[3] = (fileSize << 8) >> 24;
		byteData.data[4] = (fileSize << 16) >> 24;
		byteData.data[5] = (fileSize << 24) >> 24;

	}

	void setBeginning(int beginning)
	{
		byteData.data[6] = beginning >> 8;
		byteData.data[7] = (beginning << 24) >> 24;
	}

	void setImageSize(int width, int height)
	{
		byteData.data[8] = width >> 24;
		byteData.data[9] = (width << 8) >> 24;
		byteData.data[10] = (width << 16) >> 24;
		byteData.data[11] = (width << 24) >> 24;

		cout << unsigned(byteData.data[11]) << endl;

		width = 0;

		byteData.data[12] = height >> 24;
		byteData.data[13] = (height << 8) >> 24;
		byteData.data[14] = (height << 16) >> 24;
		byteData.data[15] = (height << 24) >> 24;
	}

	void setColorSet(char value)
	{
		byteData.data[16] = value;
	}

	void loadColorSet(char * colorSet)
	{
		for (int i = 0; i < 192; ++i)
		{
			byteData.data[i + 17] = colorSet[i];
		}
	}
};