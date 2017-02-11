#include "Enemy.h"
#include "../StateMachine/StateMachine.h"

using namespace cocos2d;


Enemy::Enemy()
{
}
Enemy::~Enemy()
{

}

bool Enemy::init(Sprite* enemySprite, int level, float moveSpeed, float radius)
{
	m_pEnemySprite = enemySprite;
	m_pStateMachine = new StateMachine();
	m_BasePosition = enemySprite->getPosition();
	m_ActiveRadius = radius;
	m_MoveSpeed = moveSpeed;

	return true && m_pStateMachine->init(this);
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