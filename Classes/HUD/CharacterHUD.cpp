#include "CharacterHUD.h"
#include "../Libs/tinyxml2.h"
#include "../GameStandart.h"

using namespace cocos2d;

bool CharacterHUD::init(const char* pathToXML, Node* pRootNode)
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

	m_DefaultCamera = Camera::getDefaultCamera();


	return m_pCurMoveTarget != nullptr;
}

void CharacterHUD::onMouseDown(cocos2d::Vec2 worldPosition, float delayTime)
{
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
}
void CharacterHUD::onCharacterReachedWayPoint()
{
	m_pCurMoveTarget->setVisible(false);
}

void CharacterHUD::addUINode(cocos2d::Node* uiNode)
{
	
}

void update(float deltaTime)
{
	// updates all UI elements to camera space
/*	for (int i = 0; i < m_UINodes.Lenght(); i++)
	{
		Vec3 curPosition = mUINodes[i]->getPosition();
		m_UINodes[i]->setPosition(m_DefaultCamera->getPosition() - curPosition);
	}*/
}