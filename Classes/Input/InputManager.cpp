#include "InputManager.h"
#include "../HelloWorldScene.h"

using namespace cocos2d;

bool InputManager::init(HelloWorld* pGame)
{
	// Set up input listeners
	auto toucheListener = EventListenerTouchOneByOne::create();
	auto mouseListener = EventListenerMouse::create();
	toucheListener->onTouchEnded = CC_CALLBACK_2(InputManager::onTouchEnded, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	pGame->addEventListenerWithSceneGraphPriority(toucheListener);
	pGame->addEventListenerWithSceneGraphPriority(mouseListener);

	return true;
}

void InputManager::onMouseDown(Event* event)
{
	// Cauculate new position and rotation
	EventMouse* e = (EventMouse*)event;
	
}

void InputManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
}