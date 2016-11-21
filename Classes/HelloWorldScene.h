#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Character;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
	cocos2d::Node* getRootNode();
	void addEventListenerWithSceneGraphPriority(cocos2d::EventListener* listener);


private:
	cocos2d::Node* pRootNode;
	std::shared_ptr<Character> wizardChar;
};

#endif // __HELLOWORLD_SCENE_H__
