#include "cocos2d.h"

class Spell
{
public:
	Spell();
	~Spell();
	bool init(cocos2d::Vec2* basePosition, cocos2d::Sprite* particle, float spellDamage, float range);
	virtual void cast(cocos2d::Vec2 direction);

protected:
	cocos2d::Vec2* m_BasePosition;
	cocos2d::Sprite* m_Particle;
	float m_TravelSpeed;
	float m_SpellDamage;
	float m_Range;
	float m_CoolDown;	
};