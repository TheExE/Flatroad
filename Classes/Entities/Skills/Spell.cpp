#include "Spell.h"

using namespace cocos2d;

Spell::Spell()
{
}
Spell::~Spell()
{
}
bool Spell::init(Node* pSpellLayer, SpellType type, Sprite* particle, float spellDamage, float range)
{
	m_SpellType = type;
	m_SpellDamage = spellDamage;
	m_Range = range;
	m_CoolDown = 1;
	m_TravelSpeed = 30;
	
	// Init spell whit texture from given sprite
	this->initWithTexture(particle->getTexture());
	
	/*
	 * Add spell to scene and make it invisible so that it does not
	 * affect things but is ready to be cast
	 */
	pSpellLayer->addChild(this);
	setVisible(false);
	

	return particle != nullptr;
}
void Spell::cast(Vec2 basePosition, Vec2 direction)
{
	setPosition(basePosition);
	setVisible(true);
	Vec2 targetPosition = basePosition + (direction.getNormalized() * m_Range);
	float duration = (targetPosition - getPosition()).length() / m_TravelSpeed;
	
	// Move the spell particle to destination and then call onFinish function
	
	stopActionByTag(MOVE_ACTION_TAG); // First need to stop previouse spell cast
	
	FiniteTimeAction* move = MoveTo::create(duration, targetPosition);
	auto moveCallBack = CallFuncN::create(CC_CALLBACK_0(Spell::onSpellCastFinished, this));
	Vector<FiniteTimeAction*> allActions;
	allActions.pushBack(move);
	allActions.pushBack(moveCallBack);
	Sequence* sequence = Sequence::create(allActions);
	sequence->setTag(MOVE_ACTION_TAG);
	runAction(sequence);

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
Spell* Spell::create(Node* pSpellLayer, SpellType spellType, Sprite* particle,
	float dmg, float range)
{
	Spell* s = new Spell();
	if(s->init(pSpellLayer, spellType, particle, dmg, range))
	{
		s->autorelease();
	}
	else
	{
		log("Spell: Failed to initialize %s", spellType);
		CC_SAFE_DELETE(s);
	}

	return s;
}

void Spell::onSpellCastFinished()
{
	setVisible(false);
}