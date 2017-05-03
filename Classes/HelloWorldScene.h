#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Character;
class InputManager;
class CameraController;
class CharacterHUD;
class Enemy;

class HelloWorld : public cocos2d::Layer
{
public:
	~HelloWorld();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
	void update(float deltaTime) override;

	void initSceneUI();
	Node* getRootNode();
	void addEventListenerWithSceneGraphPriority(cocos2d::EventListener* listener);
	void receiveInput(cocos2d::Vec2 screenPosInput);
	void receivedKeyboardInput(cocos2d::EventKeyboard::KeyCode keyCode);

private:
	Node* m_pRootNode;
	Character* m_pWizardChar;
	InputManager*  m_pInputManager;
	CameraController* m_pCameraController;
	CharacterHUD* m_pCharacterHUD;
	Enemy* m_pEnemy;
	

private:
	cocos2d::Vec2 screenPositionToWorldPosition(cocos2d::Vec2 screenPosition);
};

#endif // __HELLOWORLD_SCENE_H__
