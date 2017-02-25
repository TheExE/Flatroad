#include "Spell.h"

using namespace cocos2d;

Spell::Spell()
{

}
Spell::~Spell()
{

}
bool Spell::init(Vec2* basePosition, Sprite* particle, float spellDamage, float range)
{
	m_Particle = particle;
	m_SpellDamage = spellDamage;
	m_Range = range;
	m_CoolDown = 1;
	m_TravelSpeed = 10;
	m_BasePosition = m_BasePosition;
	m_Particle->setVisible(false);
}
void Spell::cast(Vec2 direction)
{
	m_Particle->setPosition(*m_BasePosition);
	m_Particle->setVisible(true);
	Vec2 targetPosition = *(m_BasePosition)+(direction.getNormalized() * m_Range);
	float duration = (targetPosition - m_Particle->getPosition()).length() / m_TravelSpeed;
	Action* moveTo = MoveTo::create(duration, targetPosition);
	m_Particle->runAction(moveTo);

	// TODO: Need callback when position reached so that we can disable visibility 
	// Also we still need update method because we need to check collision.
}
