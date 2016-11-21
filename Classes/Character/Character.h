#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"

class CharAnimationComponent;

class Character: public cocos2d::Sprite
{
public:
	Character();
	~Character();
	
	bool init(const char* pathToXML);

private:
	std::string mBaseSpriteFrameName;
	cocos2d::SpriteBatchNode* mWalkSpritebatch;
	cocos2d::Vector<cocos2d::SpriteFrame*> mWalkFrames;

private:
	// Inits
	void initGraphics(const char* pathToXML);
	
	// Utils
	cocos2d::Vec2 getSpriteHeading(cocos2d::Sprite* sprite);
	cocos2d::Vec2 getTouchInWorldPosition(cocos2d::Vec2 screenPos);

	// Event responders
	void onStartMoving(cocos2d::Vec2 clickScreenPos);
	void onCharacterMoveFinished();
};
