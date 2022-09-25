#pragma once
#include <iostream>
using namespace std;

template<class VST>
class Visit
{
	void operator()(VST& data)
	{
		cout << "Visit data: " << data << endl;
	}
};