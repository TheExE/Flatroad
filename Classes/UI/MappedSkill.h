#pragma once

#include "cocos2d.h"

enum SpellType;

class MappedSkill
{
public:
	MappedSkill(cocos2d::Sprite* pCellBg, SpellType spellType, cocos2d::Sprite* pSpellSprite = nullptr);
	
	// get -- set
	cocos2d::Sprite* getSpellSprite() const;
	cocos2d::Sprite* getCellSprite() const;
	SpellType getSpellType() const;
	void setSpell(cocos2d::Sprite* pSpellSprite, SpellType spellType);

private:
	cocos2d::Sprite* m_pCellBg;
	cocos2d::Sprite* m_pSpellSprite;
	SpellType m_SpellType;
};
