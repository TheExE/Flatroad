#include "InputManager.h"
#include "../HelloWorldScene.h"

using namespace cocos2d;

InputManager::InputManager()
{

}
InputManager::~InputManager()
{

}
bool InputManager::init(HelloWorld* pGame)
{
	this->pGame = pGame;

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
	pGame->notifyCurCharacterAboutInput(((EventMouse*)event)->getLocationInView());
}

void InputManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	pGame->notifyCurCharacterAboutInput(touch->getLocationInView());
}