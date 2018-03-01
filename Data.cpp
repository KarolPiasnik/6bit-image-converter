#include "Data.h"

Data::Data()
{
}

Data::~Data()
{
}

Data::Data(int userlength)
{
	data = new char[userlength];
	for (int i = 0; i < length; ++i)
		data[i] = 0;
	length = userlength;
}

Data::Data(vector<char> v)
{
	length = v.size();
	data = new char[length];
	for (int i = 0; i < length; ++i)
		data[i] = v.at(i);
}

Data Data::operator+=(Data toAdd)
{
	if (this->length != 0 && toAdd.length != 0) {
		Data data = Data(this->length + toAdd.length);

		for (int i = 0; i < this->length; ++i)
			data.data[i] = this->data[i];

		for (int i = 0; i < toAdd.length; ++i)
			data.data[i + this->length] = toAdd.data[i];

		return data;

	}

	return Data(0);
}