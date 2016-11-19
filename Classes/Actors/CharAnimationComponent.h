#pragma once

#include "cocos2d.h"
#include "IAnimationComponent.h"

class CharAnimationComponent: public IAnimationComponent
{

public:
	static const char* gName;
	virtual const char* vGetName() const { return gName; }

	virtual bool vInit(tinyxml2::XMLNode* pData) override;
	virtual void vUpdate(float deltaTime) override;

	void playWalkAnimation(cocos2d::Sprite* keySprite);
	void stopWalkAnimation(cocos2d::Sprite* keySprite);

private:
	std::vector<cocos2d::Vector<cocos2d::SpriteFrame*>> walkFrames;
	std::vector<cocos2d::Vector<cocos2d::SpriteFrame*>> attackFrames;
	std::vector<cocos2d::Vector<cocos2d::SpriteFrame*>> idleFrames;

	cocos2d::Animation* walkAnim;
	cocos2d::Animate* animate;

private:
	cocos2d::Rect stringToRect(cocos2d::String str);

};