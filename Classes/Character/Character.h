#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"

class CharAnimationComponent;

class Character: public cocos2d::Sprite
{
public:
	Character();
	~Character();
	
	bool init(const char* pathToXML, HelloWorld* pGame);

private:
	HelloWorld* m_pGame;
	cocos2d::SpriteFrame* mBaseSpriteFrame;
	cocos2d::SpriteBatchNode* mWalkSpritebatch;
	cocos2d::Vector<cocos2d::SpriteFrame*> mWalkFrames;

private:
	// Inits
	void initGraphics(const char* pathToXML);
	
	// Utils
	cocos2d::Vec2 getSpriteHeading(cocos2d::Sprite* sprite);
	cocos2d::Vec2 getTouchInWorldPosition(cocos2d::Vec2 screenPos);
	std::vector<float> stringToVector(cocos2d::String str);

	// Event responders
	void onMouseDown(cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onCharacterMoveFinished();
};
