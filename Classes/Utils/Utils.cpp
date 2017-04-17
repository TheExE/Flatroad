#include "Utils.h"
#include "GameStandart.h"

using namespace cocos2d;

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
Vec2 Utils::getSpriteHeading(Sprite* sprite)
{
	Vec2 playerPos = sprite->getPosition();
	float rotationRad = sprite->getRotation() * PI / 180;
	return Vec2(playerPos.x + (rotationRad), playerPos.y + (rotationRad));
}

Color3B Utils::stringToColor(cocos2d::String str, const char* delimiter)
{
	// Split string by delimiter
	Array* colorValArray = str.componentsSeparatedByString(delimiter);

	// In case of error return PINK
	if (colorValArray->count() != 2) return  Color3B(255, 192, 203);

	// Get the component values
	int r = (int)colorValArray->data->arr[0];
	int g = (int)colorValArray->data->arr[1];
	int b = (int)colorValArray->data->arr[2];

	// Return the read color
	return Color3B(r, g, b);
}