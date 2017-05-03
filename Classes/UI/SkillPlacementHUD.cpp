#include "UI/SkillPlacmentHUD.h"
#include "GameStandart.h"
#include <System/Utils/Utils.h>

using namespace cocos2d;

SkillPlacementHUD::SkillPlacementHUD()
{
	
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

		// Set up the hud background
		hudBg->setContentSize(Size(SCREEN_WIDTH, SCREEN_HEIGHT/10));
		hudBg->setAnchorPoint(Vec2(0, 0));
		hudBg->setColor(Color3B::GRAY);

		// Set up the cell background
		hudCellBg->setContentSize(Size(CELL_SIZE, CELL_SIZE));
		hudCellBg->setColor(Color3B::ORANGE);
		hudCellBg->setAnchorPoint(Vec2(0, 0));
		hudCellBg->setPosition(100, 8);
		hudBg->addChild(hudCellBg);

		// Add all other hud cells
		Vec2 curPos = hudCellBg->getPosition();
		for(unsigned int i = 1; i < MAX_SKILL_IN_HUD; i++) // start at 1 since the first 
		{													// was already added
			curPos = Vec2(curPos.x + 50 + CELL_SIZE, curPos.y);
			Sprite* pCurSprite = Sprite::createWithTexture(hudCellBg->getTexture());
			pCurSprite->setContentSize(Size(CELL_SIZE, CELL_SIZE));
			pCurSprite->setColor(hudCellBg->getColor());
			pCurSprite->setAnchorPoint(Vec2(0, 0));
			pCurSprite->setPosition(curPos);
			hudBg->addChild(pCurSprite);
		}

		// Add to the layer
		hud->addChild(hudBg);
	}
	else
	{
		CC_SAFE_DELETE(hud);
	}

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