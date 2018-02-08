#pragma once
#include <vector>
using namespace std;

class Data 
{
public:
	Data();
	~Data();
	char * data;
	int length = 0;

	Data(int userlength);
	Data(vector<char> v);
	Data operator+=(Data toAdd);
};

