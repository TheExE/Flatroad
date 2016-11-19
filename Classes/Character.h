#pragma once

#include "cocos2d.h"
#include "Actors/Actor.h"

class CharAnimationComponent;

class Character: public Actor
{
public:
	Character();
	~Character();
	
	static const char* gName;
	virtual const char* vGetName() const { return gName; }

	void update();
	virtual void postInit() override;

private:
	cocos2d::Sprite* mCharSprite;
	std::shared_ptr<CharAnimationComponent> mAnimationComp;

private:
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	cocos2d::Vec2 getSpriteHeading(cocos2d::Sprite* sprite);
	cocos2d::Vec2 getTouchInWorldPosition(cocos2d::Vec2 screenPos);
	void onCharacterMoveFinished();
};
