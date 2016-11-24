#pragma once

#include "cocos2d.h"

class CharacterHUD
{
public:
	bool init(const char* pathToXML, cocos2d::Node* pRootNode);
	void onMouseDown(cocos2d::Vec2 worldPosition, float delayTime);

private:
	cocos2d::Sprite* m_pCurMoveTarget;

private:
	void onCharacterReachedWayPoint();
};