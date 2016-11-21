#pragma once

#include "cocos2d.h"

class CharacterHUD
{
public:
	CharacterHUD();
	~CharacterHUD();
	bool init(const char* pathToXML);

private:
	cocos2d::Sprite mCurMoveTarget;

private:
	void onMouseDown(cocos2d::Event event);

};