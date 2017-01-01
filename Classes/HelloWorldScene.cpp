#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "Input/InputManager.h"
#include "Camera/CameraController.h"
#include "GameStandart.h"
#include "HUD/CharacterHUD.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// init and add root node to this layer
	pRootNode = CSLoader::createNode("MainScene.csb");
	addChild(pRootNode);

	m_pWizardChar.reset(new Character());
	if (!m_pWizardChar->init("Assets/CharacterDefs/WizardCharacter.xml"))
	{
		cocos2d::log("HelloWorldScene: %s", "Failed to initialize wiz character !");
	}
	m_pCameraController.reset(new CameraController());
	if(!m_pCameraController->init(m_pWizardChar.get()))
	{
		cocos2d::log("HelloWorldScene: Failed to initialize Camera controller !");
	}
	m_pCharacterHUD.reset(new CharacterHUD());
	if (!m_pCharacterHUD->init("Assets/CharacterDefs/HUD.xml", pRootNode))
	{
		cocos2d::log("HelloWorldScene: Failed to initiazlize Character controller !");
	}

	pRootNode->addChild(m_pWizardChar.get());
	return true;
}

void HelloWorld::update(float deltaTime) {}
void HelloWorld::receiveInput(cocos2d::Vec2 screenPosInput)
{
	// Cauculate move speed
	Vec2 clickInWorld = screenPositionToWorldPosition(screenPosInput);
	float distanceToTravel = getPosition().distance(clickInWorld);
	float moveTime = distanceToTravel / CHARACTER_MOVE_SPEED;

	// Inform character and camera to move
	m_pWizardChar->onStartMoving(clickInWorld, moveTime);
	m_pCameraController->moveCameraTo(clickInWorld, moveTime);

	// Draw HUD point at target area
	m_pCharacterHUD->onMouseDown(clickInWorld, moveTime);
}
Node* HelloWorld::getRootNode()
{
	return pRootNode;
}
void HelloWorld::addEventListenerWithSceneGraphPriority(EventListener* listener)
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
Vec2 HelloWorld::screenPositionToWorldPosition(cocos2d::Vec2 screenPosition)
{
	Vec2 playerCharPos = m_pWizardChar->getPosition();
	return Vec2(playerCharPos.x + (screenPosition.x - (SCREEN_WIDTH / 2)),
		playerCharPos.y + ((screenPosition.y - (SCREEN_HEIGHT / 2)) * (-1)));
}
void receivedKeyboardInput(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_1:
			
		break;

	default:
		break;
	}
}
void HelloWorld::initSceneUI()
{
	// Insert main layer
	auto uiLayer = CSLoader::createNode("BaseUI.csb");
	Camera::getDefaultCamera()->addChild(uiLayer);

	// 
	m_pInputManager.reset(new InputManager());
	if (!m_pInputManager->init(uiLayer, this))
	{
		cocos2d::log("HelloWorldScene: Failed to initialize input manager !");
	}
}
void HelloWorld::onEnter()
{
	initSceneUI();
}