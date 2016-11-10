#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
  
    if ( !Layer::init() )
    {
        return false;
    }
	touchInfo = Label::create();
	touchInfo->setPosition(100, 100);
	playerCharacter = Sprite::create();
	Sprite* characterSpriteSheet = Sprite::create("Assets/Graphics/Player/player-move.png");
	Vector<SpriteFrame*> wizardFrames;
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(0, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(32, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(64, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(96, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(128, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(160, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(192, 0, 32, 32)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(224, 0, 32, 32)));
	Animation* animation = Animation::createWithSpriteFrames(wizardFrames, 0.1);
	Animate* animate = Animate::create(animation);
	playerCharacter->runAction(RepeatForever::create(animate));
	playerCharacter->setPosition(500, 300);

	auto rootNode = CSLoader::createNode("MainScene.csb");
	rootNode->addChild(playerCharacter);
	addChild(rootNode);


	// Input init
	auto toucheListener = EventListenerTouchOneByOne::create();
	auto mouseListener = EventListenerMouse::create();
	toucheListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::OnTouchEnded, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::OnMouseDown, this);

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(toucheListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void HelloWorld::OnTouchEnded(Touch* touch, Event* event)
{
	Vec2 touchPos = convertToWorldSpace(touch->getLocation());
	touchPos.y = this->getContentSize().height - touchPos.y;
	float distanceToTravel = playerCharacter->getPosition().distance(touchPos);
	auto move = MoveTo::create(distanceToTravel / 15, touchPos);
	playerCharacter->runAction(move);
}
void HelloWorld::OnMouseDown(cocos2d::Event* event)
{
	EventMouse* e = (EventMouse*)event;
	Vec2 clickPos = convertToWorldSpace(e->getLocation());
	clickPos.y = this->getContentSize().height - clickPos.y;
	float distanceToTravel = playerCharacter->getPosition().distance(clickPos);
	auto move = MoveTo::create(distanceToTravel/25, clickPos);
	playerCharacter->runAction(move);
	
	auto move = MoveTo::create(distanceToTravel / 25, clickPos);
	playerCharacter->runAction(move);
	auto cam = Camera::getDefaultCamera();
	cam->runAction(move);

	// TODO: Need to move camera and make player stick to center of the screen
}
