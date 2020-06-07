#pragma once
#include <vector>
#include <string>

using namespace std;

struct Manager
{
	void commands();

	vector <string> splitLine(string line); // За тази функция съм получил чужда помощ
};

