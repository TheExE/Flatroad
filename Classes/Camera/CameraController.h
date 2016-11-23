#pragma once

#include "cocos2d.h"

class Character;

class CameraController
{
public:
	bool init(cocos2d::Camera* pMainCamera, Character* pCurCharacter);
	void moveCameraTo(cocos2d::Vec2 worldPosition, float movementSpeed);

private:
	Character* m_pCurCharacter;
};