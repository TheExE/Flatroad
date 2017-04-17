#include "Enemy.h"
#include "../StateMachine/StateMachine.h"
#include <cmath>
#include "../Entities/Spell.h"

using namespace cocos2d;


Enemy::Enemy()
{
	m_pStateMachine = NULL;
	m_pEnemySprite = NULL;
}
Enemy::~Enemy()
{

}

bool Enemy::init(Sprite* enemySprite, int level, float moveSpeed, float radius)
{
	m_pEnemySprite = enemySprite;
	m_pStateMachine = new StateMachine();
	m_BasePosition = Vec2(enemySprite->getPosition());
	m_ActiveRadius = radius;
	m_MoveSpeed = moveSpeed;
	m_DamageDealt = level + log10(level);
	m_SpellList.push_back(new Spell());
	m_SpellList.at(0)->init(enemySprite, 50, 100);

	return m_pStateMachine->init(this);
}

void Enemy::update(float deltaTime)
{
	m_pStateMachine->update(deltaTime);
}

Sprite* Enemy::getSprite() const
{
	return m_pEnemySprite;
}
float Enemy::getActiveRadius() const
{
	return m_ActiveRadius;
}
Vec2 Enemy::getBasePosition() const
{
	return m_BasePosition;
}
float Enemy::getMovementSpeed() const
{
	return m_MoveSpeed;
}