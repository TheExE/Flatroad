#include "CharacterHUD.h"
#include "../Libs/tinyxml2.h"


bool CharacterHUD::init(const char* pathToXML)
{
	// Load the file
	tinyxml2::XMLDocument doc;
	std::string absPath = "../Resources/res/";
	tinyxml2::XMLError err = doc.LoadFile((absPath + pathToXML).c_str());
	if (err)
	{
		cocos2d::log("CharacterHUD: XML file not found: %s", pathToXML);
	}
	tinyxml2::XMLNode* pData = doc.RootElement();
	tinyxml2::XMLNode* pWayPointPath = pData->FirstChild();
	m_pCurMoveTarget = cocos2d::Sprite::create(pWayPointPath->FirstChild()->ToText()->Value());
	if (m_pCurMoveTarget)
	{
		m_pCurMoveTarget->setVisible(false);
	}


	return m_pCurMoveTarget != nullptr;
}

void CharacterHUD::onMouseDown(cocos2d::Vec2 worldPosition)
{
	m_pCurMoveTarget->setPosition(worldPosition);
	m_pCurMoveTarget->setVisible(true);
}
void CharacterHUD::onCharacterReachedWayPoint()
{
	m_pCurMoveTarget->setVisible(false);
}