#pragma once

#include "cocos2d.h"

class CharacterHUD
{
public:
	bool init(const char* pathToXML);
	void onCharacterReachedWayPoint();

private:
	cocos2d::Sprite* m_pCurMoveTarget;

private:
	void onMouseDown(cocos2d::Vec2 worldPosition);
};