#include "InputManager.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

InputManager::InputManager()
{

}
InputManager::~InputManager()
{

}
bool InputManager::init(Node* pInputLayer, HelloWorld* pGame)
{
	m_pInputLayer = pInputLayer;
	m_pGame = pGame;

	// Set up input listeners
	auto toucheListener = EventListenerTouchOneByOne::create();
	auto mouseListener = EventListenerMouse::create();
	auto keyBoardListener = EventListenerKeyboard::create();
	toucheListener->onTouchEnded = CC_CALLBACK_2(InputManager::onTouchEnded, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyboardDown, this);
	pInputLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, m_pInputLayer);

	return true;
}

void InputManager::onMouseDown(Event* event)
{
	m_pGame->receiveInput(((EventMouse*)event)->getLocation());
}

void InputManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_pGame->receiveInput(touch->getLocation());
}
void InputManager::onKeyboardDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}