#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Character;
class InputManager;
class CameraController;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
	void update(float deltaTime) override;

	cocos2d::Node* getRootNode();
	void addEventListenerWithSceneGraphPriority(cocos2d::EventListener* listener);
	void notifyCurCharacterAboutInput(cocos2d::Vec2 screenPosInput);


private:
	cocos2d::Node* pRootNode;
	std::shared_ptr<Character> m_pWizardChar;
	std::shared_ptr<InputManager>  m_pInputManager;
	std::shared_ptr<CameraController> m_pCameraController;
};

#endif // __HELLOWORLD_SCENE_H__
