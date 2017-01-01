#pragma once

#include "cocos2d.h"

class CharacterHUD
{
public:
	bool init(const char* pathToXML, cocos2d::Node* pRootNode);
	void onMouseDown(cocos2d::Vec2 worldPosition, float delayTime);
	void update(float deltaTime);

private:
	cocos2d::Sprite* m_pCurMoveTarget;
	cocos2d::Vector<cocos2d::Node*> m_UINodes;
	cocos2d::Camera* m_DefaultCamera;

	void addUINode(cocos2d::Node* uiNode);
	void onCharacterReachedWayPoint();
};