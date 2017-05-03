#include "Spell.h"

using namespace cocos2d;

Spell::Spell()
{

}
Spell::~Spell()
{

}
bool Spell::init(SpellType type, Sprite* particle, float spellDamage, float range)
{
	m_SpellType = type;
	m_Particle = particle;
	m_SpellDamage = spellDamage;
	m_Range = range;
	m_CoolDown = 1;
	m_TravelSpeed = 10;
	m_Particle->setVisible(false);

	return particle != nullptr;
}
void Spell::cast(Vec2 basePosition, Vec2 direction)
{
	m_Particle->setPosition(basePosition);
	m_Particle->setVisible(true);
	Vec2 targetPosition = basePosition + (direction.getNormalized() * m_Range);
	float duration = (targetPosition - m_Particle->getPosition()).length() / m_TravelSpeed;
	Action* moveTo = MoveTo::create(duration, targetPosition);
	m_Particle->runAction(moveTo);

	// TODO: Need callback when position reached so that we can disable visibility 
	// Also we still need update method because we need to check collision.
}
SpellType Spell::GetType() const
{
	return m_SpellType;
}

/*
 * Creates new spell from provided parameters. This tries to follow
 * cocos2d convetions with static create methods. 
 */
Spell* Spell::create(SpellType spellType, cocos2d::Sprite* particle,
	float dmg, float range)
{
	Spell* s = new Spell();
	if(s->init(spellType, particle, dmg, range))
	{
		s->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(s);
	}

	return s;
}