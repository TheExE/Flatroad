#pragma once

#include "IDrawComponent.h"
#include "cocos2d.h"

class SpriteComponent : public IDrawComponent
{
public:
	static const char* gName;
	virtual const char* vGetName() const { return gName; }

	virtual bool vInit(tinyxml2::XMLNode* pData) override;
	virtual void vUpdate(float deltaTime) override;
	cocos2d::Sprite* getSprite() const;

private:
	cocos2d::Sprite* spriteToDraw;
};