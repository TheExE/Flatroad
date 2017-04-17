#pragma once

#include "cocos2d.h"

class BoxedPhysics
{
	// Functions 
public:
	BoxedPhysics();
	~BoxedPhysics();
	bool init();
	bool addRectToTheWorld(cocos2d::Rect& rect);

private:
	bool overlap(cocos2d::Rect a, cocos2d::Rect b);
	bool checkCollision();

	// Veriables
private:
	std::vector<cocos2d::Rect&> m_BoxWorld;
};

