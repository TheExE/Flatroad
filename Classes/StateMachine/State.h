#pragma once

class Enemy;

class State
{
public:
	virtual ~State() {};
	virtual bool onEnter(Enemy* pTargetEnemy) = 0;
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onExit() = 0;
};
