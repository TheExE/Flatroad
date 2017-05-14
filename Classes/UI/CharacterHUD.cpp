#include "CharacterHUD.h"
#include "GameStandart.h"
#include "System/Libs/tinyxml2.h"
#include "System/Utils/Utils.h"
#include "SkillPlacmentHUD.h"
#include <Entities/Skills/SpellType.h>

using namespace cocos2d;

bool CharacterHUD::init(const char* pathToXML, Node* pRootNode, Node* pUINode)
{
	// Load the file
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.LoadFile(Utils::appendFullPathToAssetsPath(pathToXML).c_str());
	if (err)
	{
		cocos2d::log("CharacterHUD: XML file not found: %s", pathToXML);
	}
	tinyxml2::XMLNode* pData = doc.RootElement();
	
	//--- Init move target HUD
	tinyxml2::XMLNode* pXMLWalkPointPath = pData->FirstChildElement(XML_WALKPOINT);
	std::string  walkPoint = Utils::appendFullPathToAssetsPath(
		pXMLWalkPointPath->FirstChild()->ToText()->Value());
	m_pCurMoveTarget = cocos2d::Sprite::create(walkPoint);
 
	// In case of error log the path to see if its correct
	if(m_pCurMoveTarget == nullptr)
	{
		cocos2d::log("CharacterHUD: Way point graphics not found ! %s", walkPoint.c_str());
	}

	// Since move target should appear under buttons and menus it is added before UI node
	m_pCurMoveTarget->setVisible(false);
	m_pCurMoveTarget->setLocalZOrder(Z_ORDER_WAYPOINT); // Ensures that it also appears under character
	pRootNode->addChild(m_pCurMoveTarget);

	//--- Init Skill placement HUD
	m_pSkillPlacementHUD = SkillPlacementHUD::create(pData);
	if(m_pSkillPlacementHUD == nullptr)
	{
		cocos2d::log("CharacterHUD: Failed to initialize SkillPlacementHUD !");
	}
	else
	{
		pUINode->addChild(m_pSkillPlacementHUD);
	}
	pRootNode->addChild(pUINode);
	m_pUINode = pUINode;

	return m_pCurMoveTarget != nullptr;
}

void CharacterHUD::onMouseDown(cocos2d::Vec2 worldPosition, float delayTime)
{
	// Setting up move point on map
	m_pCurMoveTarget->setPosition(worldPosition);
	m_pCurMoveTarget->setVisible(true);

	FiniteTimeAction* delayAction = DelayTime::create(delayTime);
	auto delayedCallBack = CallFuncN::create(CC_CALLBACK_0(CharacterHUD::onCharacterReachedWayPoint, this));
	cocos2d::Vector<FiniteTimeAction*> allActions;
	allActions.pushBack(delayAction);
	allActions.pushBack(delayedCallBack);

	Sequence* sequence = Sequence::create(allActions);
	sequence->setTag(MOVE_TARGET_ACTION_TAG);
	
	// Stop any already running dalay actions
	m_pCurMoveTarget->stopActionByTag(MOVE_TARGET_ACTION_TAG);
	m_pCurMoveTarget->runAction(sequence);


	// Move baseUI along camera
	m_pUINode->stopActionByTag(MOVE_UI_ACTION_TAG);
	Vec2 halfScreen = Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Action* moveUI = MoveTo::create(delayTime, worldPosition - halfScreen);
	moveUI->setTag(MOVE_UI_ACTION_TAG);
	m_pUINode->runAction(moveUI);
}
void CharacterHUD::onCharacterReachedWayPoint()
{
	m_pCurMoveTarget->setVisible(false);
}
SpellType CharacterHUD::getSpellTypeFromPlacementPos(SkillPlacementPosition pos)
{
	return m_pSkillPlacementHUD->getSpellTypeFromPlacementPos(pos);
}
void CharacterHUD::update(float deltaTime)
{
}