#include "cocos2d.h"
#include "SpellType.h"

class Spell: public cocos2d::Ref
{
public:
	Spell();
	~Spell();
	static Spell* create(SpellType spellType, cocos2d::Sprite* particle,
			float dmg, float range);
	bool init(SpellType type, cocos2d::Sprite* particle, float spellDamage, float range);
	virtual void cast(cocos2d::Vec2 basePosition, cocos2d::Vec2 direction);
	virtual SpellType GetType() const;

protected:
	cocos2d::Sprite* m_Particle;
	float m_TravelSpeed;
	float m_SpellDamage;
	float m_Range;
	float m_CoolDown;
	SpellType m_SpellType;
};