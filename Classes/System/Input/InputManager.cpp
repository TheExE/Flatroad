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

		// Create the listener objects
	auto mouseListener = EventListenerMouse::create();
	auto keyBoardListener = EventListenerKeyboard::create();

		// Assign callbacks
	mouseListener->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_1(InputManager::onKeyboardDown, this);

		// Add listeners to listening list
	pInputLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener,
		m_pInputLayer);
	pInputLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener,
		m_pInputLayer);


	return true;
}

void InputManager::onMouseDown(Event* event) const
{
	m_pGame->receiveMomentInput(((EventMouse*)event)->getLocation());
}
void InputManager::onKeyboardDown(EventKeyboard::KeyCode keyCode) const
{
	m_pGame->receivedKeyboardInput(keyCode);
}