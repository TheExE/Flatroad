#pragma once

#include "cocos2d.h"
#include "System/Libs/tinyxml2.h"

enum SkillPlacementPosition
{
	Position_1,
	Position_2,
	Position_3,
	Position_4,
	Position_5,
	Position_6,
	Position_7,
	Position_8,
	Position_9,
};

enum SpellType;
class MappedSkill;

class SkillPlacementHUD: public cocos2d::Layer
{
public:
	~SkillPlacementHUD();
	static SkillPlacementHUD* create(tinyxml2::XMLNode* pData);
	void setSkill(cocos2d::Sprite* pSkillSprite, SkillPlacementPosition pos, SpellType spellType);
	SpellType getSpellTypeFromPlacementPos(SkillPlacementPosition pos);
	
	void setHUDBackground(cocos2d::Sprite* pBg);
	void setCellBackground(cocos2d::Sprite* pCellBg);
	cocos2d::Sprite* getHUDBackground() const;
	cocos2d::Sprite* getCellBackground() const;

private:
	cocos2d::Sprite* m_pBackground;
	cocos2d::Sprite* m_pCellBackground;
	std::vector<MappedSkill*> m_MapedSkills;

private:
	SkillPlacementHUD();
};