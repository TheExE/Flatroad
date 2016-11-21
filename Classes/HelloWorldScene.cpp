#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"


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
	wizardChar.reset(new Character());
	if (!wizardChar->init("Assets/CharacterDefs/WizardCharacter.xml"))
	{
		cocos2d::log("HelloWorldScene: %s", "Failed to initialize wiz character !");
	}
	addChild(pRootNode);
	pRootNode->addChild(wizardChar.get());


	return true;
}

Node* HelloWorld::getRootNode()
{
	return pRootNode;
}
void HelloWorld::addEventListenerWithSceneGraphPriority(EventListener* listener)
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}