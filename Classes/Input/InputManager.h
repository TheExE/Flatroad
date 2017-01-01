#pragma once

#include "cocos2d.h"

class HelloWorld;

class InputManager
{
public:
	InputManager();
	~InputManager();
	bool init(cocos2d::Node* pInputLayer, HelloWorld* pGame);

private:
	cocos2d::Node* m_pInputLayer;
	HelloWorld* m_pGame;

private:
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onKeyboardDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};