#include "Utils.h"

std::vector<float> Utils::stringToVector(cocos2d::String str)
{
	const char* cStr = str.getCString();
	std::vector<float> numbers;
	int rectIdx = 0;

	for (int index = 0; index < str.length(); index++)
	{
		if (cStr[index] != ']' && cStr[index] != '[')
		{
			// Reads the whole number
			std::string wholeNumber = "";
			while (cStr[index] != ',' && cStr[index] != ']')
			{
				wholeNumber += cStr[index];
				index++;
			}

			// Transforms numbers in string format to integer format
			numbers.push_back(atof(wholeNumber.c_str()));
			rectIdx++;
		}
	}
	return numbers;
}