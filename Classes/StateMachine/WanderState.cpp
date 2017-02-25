#include "WanderState.h"
#include "../Enemy/Enemy.h"
#include "../GameStandart.h"

using namespace cocos2d;

WanderState::WanderState()
	:
	State()
{
    
}
bool WanderState::onEnter(Enemy* pTargetEnemy)
{
	cocos2d::log("Enemy entered: wander state !!!");
	m_pTargetEnemy = pTargetEnemy;
	m_CurTargetPosition = getRandomPosInRange();
	m_IsMoving = true;
	m_CurTimeWaited = 0;

	return pTargetEnemy != nullptr;
}
void WanderState::onUpdate(float deltaTime)
{
	if (!m_IsMoving)
	{
		m_CurTimeWaited += deltaTime;
		if (m_CurTimeWaited > WAITE_BETWEEN_WANDER)
		{
			m_IsMoving = true;
			m_CurTargetPosition = getRandomPosInRange();
			m_CurTimeWaited = 0;
		}
	}
	else
	{
		// Walk to cur target position
		Vec2 curPosition = m_pTargetEnemy->getSprite()->getPosition();
		Vec2 toTargetPosition = (m_CurTargetPosition - curPosition);
		Vec2 toTargetPositionNormalized = toTargetPosition.getNormalized();
	
		float enemySpeed = m_pTargetEnemy->getMovementSpeed()*deltaTime;
		m_pTargetEnemy->getSprite()->setPosition(curPosition + 
			(toTargetPositionNormalized * enemySpeed));

		// Agent has arrived at destination
		float distanceToTarget = toTargetPosition.length();
		if ( distanceToTarget < enemySpeed )
		{
			m_IsMoving = false;
		}
	}
}
void WanderState::onExit()
{

}
Vec2 WanderState::getRandomPosInRange()
{
	float radius = m_pTargetEnemy->getActiveRadius();
	float newX = RandomHelper::random_int<int>(-radius, radius);
	float newY = RandomHelper::random_int<int>(-radius, radius);
	Vec2* basePosition = &m_pTargetEnemy->getBasePosition();

	return Vec2(basePosition->x + newX, basePosition->y + newY);
}

