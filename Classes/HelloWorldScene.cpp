#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "Input/InputManager.h"
#include "Camera/CameraController.h"

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

	pRootNode = CSLoader::createNode("MainScene.csb");
	m_pWizardChar.reset(new Character());
	if (!m_pWizardChar->init("Assets/CharacterDefs/WizardCharacter.xml"))
	{
		cocos2d::log("HelloWorldScene: %s", "Failed to initialize wiz character !");
	}
	m_pInputManager.reset(new InputManager());
	if (!m_pInputManager->init(this))
	{
		cocos2d::log("HelloWorldScene: Failed to initialize input manager !");
	}
	/*m_pCameraController.reset(new CameraController());
	if(!m_pCameraController->init(Camera::getDefaultCamera(), m_pWizardChar.get()))
	{
		cocos2d::log("HelloWorldScene: Failed to initialize Camera controller !");
	}*/
	
	
	addChild(pRootNode);
	pRootNode->addChild(m_pWizardChar.get());


	return true;
}
void HelloWorld::update(float deltaTime)
{
	//m_pCameraController->update();
}

void HelloWorld::notifyCurCharacterAboutInput(cocos2d::Vec2 screenPosInput)
{
	m_pWizardChar->onStartMoving(screenPosInput);
}
Node* HelloWorld::getRootNode()
{
	return pRootNode;
}
void HelloWorld::addEventListenerWithSceneGraphPriority(EventListener* listener)
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}