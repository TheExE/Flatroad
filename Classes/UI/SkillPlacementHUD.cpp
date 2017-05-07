#include "UI/SkillPlacmentHUD.h"
#include "GameStandart.h"
#include <System/Utils/Utils.h>
#include "MappedSkill.h"
#include "Entities/Skills/SpellType.h"

using namespace cocos2d;

SkillPlacementHUD::SkillPlacementHUD()
{
	m_pCellBackground = nullptr;
	m_pBackground = nullptr;
}
SkillPlacementHUD::~SkillPlacementHUD()
{
	// Release taken memory
	for(auto i = m_MapedSkills.begin(); i < m_MapedSkills.end(); ++i)
	{
		delete (*i);
	}
}

SkillPlacementHUD* SkillPlacementHUD::create(tinyxml2::XMLNode* pData)
{
	tinyxml2::XMLNode* pSkillPlacementXML = pData->FirstChildElement(XML_SKILLPLACEMENT);
	tinyxml2::XMLNode* pBackgroundXML = pSkillPlacementXML->FirstChildElement(XML_BG);
	tinyxml2::XMLNode* pCellBgXML = pSkillPlacementXML->FirstChildElement(XML_CELL_BG);

	SkillPlacementHUD* hud = new SkillPlacementHUD();
	
	// Initialize skill placement HUD
	Sprite* hudBg = Sprite::create(Utils::appendFullPathToAssetsPath(
		Utils::getFirstChildText(pBackgroundXML)));
	Sprite* hudCellBg = Sprite::create(Utils::appendFullPathToAssetsPath(
		Utils::getFirstChildText(pCellBgXML)));
	hud->setCellBackground(hudBg);
	hud->setHUDBackground(hudCellBg);
	if(hudBg != nullptr && hudCellBg !=nullptr && hud->init())
	{
		// Count references
		hud->autorelease();
		
		/*
		 *  We have successfully initialized the layer so
		 *  lets place HUD elements into the layer
		*/

		/* 
		 * For purpose of not making unnecessary allocations, reserve all possible skill slots
		 * at begining.
		*/
		hud->m_MapedSkills.reserve(MAX_SKILL_IN_HUD);

		// Set up the hud background
		hudBg->setContentSize(Size(SCREEN_WIDTH, SCREEN_HEIGHT/10));
		hudBg->setAnchorPoint(Vec2(0, 0));
		hudBg->setColor(Color3B::GRAY);

		// Set up the cell background
		hudCellBg->setContentSize(Size(CELL_SIZE, CELL_SIZE));
		hudCellBg->setColor(Color3B::ORANGE);
		hudCellBg->setAnchorPoint(Vec2(0, 0));
		hudCellBg->setPosition(SCALE* 40, SCALE);
		hudBg->addChild(hudCellBg);
		
		// Add this hud cell to mapped skills
		hud->m_MapedSkills.push_back(new MappedSkill(hudCellBg, None));

		// Add all other hud cells
		Vec2 curPos = hudCellBg->getPosition();
		for(unsigned int i = 1; i < MAX_SKILL_IN_HUD; i++) // start at 1 since the first 
		{													// was already added
			curPos = Vec2(curPos.x + (20*SCALE) + CELL_SIZE, curPos.y);
			Sprite* pCurSprite = Sprite::createWithTexture(hudCellBg->getTexture());
			pCurSprite->setContentSize(Size(CELL_SIZE, CELL_SIZE));
			pCurSprite->setColor(hudCellBg->getColor());
			pCurSprite->setAnchorPoint(Vec2(0, 0));
			pCurSprite->setPosition(curPos);
			hudBg->addChild(pCurSprite);
			hud->m_MapedSkills.push_back(new MappedSkill(pCurSprite, None));
		}

		// Add to the layer
		hud->addChild(hudBg);
	}
	else
	{
		CC_SAFE_DELETE(hud);
	}

	// TODO: Remove this test
	// Test Skill HUD
	Sprite* skillImg = Sprite::create("res/Assets/Graphics/Skills/Spells/fireBolt.png");
	hud->setSkill(skillImg, Position_1, FireBolt);

	return hud;
}

void SkillPlacementHUD::setHUDBackground(cocos2d::Sprite* pBg)
{
	m_pBackground = pBg;
}

void SkillPlacementHUD::setCellBackground(cocos2d::Sprite* pCellBg)
{
	m_pCellBackground = pCellBg;
}
Sprite* SkillPlacementHUD::getHUDBackground() const
{
	return m_pBackground;	
}
Sprite* SkillPlacementHUD::getCellBackground() const
{
	return m_pCellBackground;
}
void SkillPlacementHUD::setSkill(Sprite* pSkillSprite, SkillPlacementPosition pos, SpellType spellType)
{
	m_MapedSkills[pos]->setSpell(pSkillSprite, spellType);
}
SpellType SkillPlacementHUD::getSpellTypeFromPlacementPos(SkillPlacementPosition pos)
{
	return m_MapedSkills.at(pos)->getSpellType();
}