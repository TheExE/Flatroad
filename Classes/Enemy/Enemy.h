#pragma once

#include "cocos2d.h"

class StateMachine;
class Spell;

class Enemy
{
public:
	Enemy();
	~Enemy();
	bool init(cocos2d::Sprite* enemySprite, int level, float moveSpeed, float radius);
	void update(float deltaTime);

	cocos2d::Sprite* getSprite() const;
	float getActiveRadius() const;
	cocos2d::Vec2 getBasePosition() const;
	float getMovementSpeed() const;

private:
	StateMachine* m_pStateMachine;
	cocos2d::Sprite* m_pEnemySprite;
	cocos2d::Vec2 m_BasePosition;
	std::vector<Spell*> m_SpellList;
	int m_Level;
	float m_Health;
	float m_MoveSpeed;
	float m_ActiveRadius;
	float m_DamageDealt;
};