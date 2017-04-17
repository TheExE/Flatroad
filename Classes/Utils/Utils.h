#pragma once

#include "cocos2d.h"


class Utils
{
public:
	static std::vector<float> stringToVector(cocos2d::String str);
	static cocos2d::Vec2 getSpriteHeading(cocos2d::Sprite* sprite);
	static cocos2d::Color3B stringToColor(cocos2d::String str, const char* delimiter);
};