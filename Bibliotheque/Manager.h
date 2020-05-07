#pragma once
#include <vector>
#include <string>

using namespace std;

struct Manager
{
	void commands();

	vector <string> splitLine(const string& line);
};

