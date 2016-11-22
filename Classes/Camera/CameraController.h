#pragma once

#include "cocos2d.h"

class Character;

class CameraController
{
public:
	bool init(cocos2d::Camera* pMainCamera, Character* pCurCharacter);
	void update();

private:
	cocos2d::Camera* m_pMainCamera;
	Character* m_pCurCharacter;
	float mCameraZCoord;
};