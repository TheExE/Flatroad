#pragma once
#include "State.h"
#include "cocos2d.h"

class Enemy;

class WanderState : public State
{
public:
    WanderState();
	
	bool onEnter(Enemy* pTargetEnemy) override;
	void onUpdate(float deltaTime) override;
	void onExit() override;

private:
	Enemy* m_pTargetEnemy;
	cocos2d::Vec2 m_CurTargetPosition;
	cocos2d::Vec2 getRandomPosInRange();

	float m_CurTimeWaited;
	bool m_IsMoving;
};
