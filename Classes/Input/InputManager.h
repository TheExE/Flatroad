#pragma once

#include "cocos2d.h"

class HelloWorld;

class InputManager
{
public:
	InputManager();
	~InputManager();
	bool init(HelloWorld* pGame);

private:
	HelloWorld* pGame;

private:
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onKeyboardDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};