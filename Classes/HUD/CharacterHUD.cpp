#include "CharacterHUD.h"
#include "../Libs/tinyxml2.h"
#include "../GameStandart.h"

using namespace cocos2d;

bool CharacterHUD::init(const char* pathToXML, Node* pRootNode, Node* pUINode)
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
	cocos2d::log(pWayPointPath->FirstChild()->ToText()->Value());
	m_pCurMoveTarget = cocos2d::Sprite::create(pWayPointPath->FirstChild()->ToText()->Value());
	if (m_pCurMoveTarget)
	{
		m_pCurMoveTarget->setVisible(false);
		pRootNode->addChild(m_pCurMoveTarget);
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

void CharacterHUD::update(float deltaTime)
{
	
	// updates all UI elements to camera space
/*	for (int i = 0; i < m_UINodes.Lenght(); i++)
	{
		Vec3 curPosition = mUINodes[i]->getPosition();
		m_UINodes[i]->setPosition(m_DefaultCamera->getPosition() - curPosition);
	}*/
}