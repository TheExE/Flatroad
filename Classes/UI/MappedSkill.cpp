#include "MappedSkill.h"
#include "Entities/Skills/SpellType.h"

using namespace cocos2d;

MappedSkill::MappedSkill(Sprite* pCellBg, SpellType spellType, Sprite* pSpellSprite)
{
	m_pCellBg = pCellBg;
	m_pSpellSprite = pSpellSprite;
	m_SpellType = spellType;
}
Sprite* MappedSkill::getSpellSprite() const
{
	return m_pSpellSprite;
}
Sprite* MappedSkill::getCellSprite() const
{
	return m_pCellBg;
}
SpellType MappedSkill::getSpellType() const
{
	return m_SpellType;
}
void MappedSkill::setSpell(Sprite* pSpellSprite, SpellType spellType)
{
	m_SpellType = spellType;
	m_pSpellSprite = pSpellSprite;
	m_pCellBg->addChild(pSpellSprite);
	Size cellSize = m_pCellBg->getContentSize();
	m_pSpellSprite->setPosition(cellSize.width / 2, cellSize.height / 2);
}
