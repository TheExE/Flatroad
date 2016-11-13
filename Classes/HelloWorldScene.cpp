#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameConsts.h"

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
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(0, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(64, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(128, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(192, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(256, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(320, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(384, 0, 64, 64)));
	wizardFrames.pushBack(SpriteFrame::createWithTexture(characterSpriteSheet->getTexture(), Rect(448, 0, 64, 64)));
	Animation* animation = Animation::createWithSpriteFrames(wizardFrames, 0.1);
	Animate* animate = Animate::create(animation);
	playerCharacter->runAction(RepeatForever::create(animate));
	playerCharacter->setAnchorPoint(Vec2(0.5, 0.5));
	playerCharacter->setPosition(0, 0);

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
}
void HelloWorld::OnMouseDown(cocos2d::Event* event)
{
	if (playerCharacter->numberOfRunningActions() < 5)
	{
		EventMouse* e = (EventMouse*)event;
		Vec2 clickPos = e->getLocation();
		
		// Move character
		
		Vec2 clickInWorld = convertToWorldSpace(clickPos);
		float distanceToTravel = playerCharacter->getPosition().distance(clickInWorld);
		float movementSpeed = distanceToTravel / 50;
		auto move = MoveTo::create(movementSpeed, clickInWorld);
		float rotateAngle = Vec2::angle(GetSpriteHeading(playerCharacter),
			clickInWorld - playerCharacter->getPosition()) * 180/ PI;
		playerCharacter->runAction(move);
		playerCharacter->setRotation(rotateAngle);

		// Move camera
		Camera* cam = Camera::getDefaultCamera();
		Action* moveCamera = MoveTo::create(movementSpeed, Vec3(clickInWorld.x, clickInWorld.y,
			cam->getPosition3D().z));
		cam->runAction(moveCamera);

		std::stringstream s;
		s << "Angle:  " << rotateAngle << std::endl;
		cocos2d::log(s.str().c_str());
		s.clear();
		s << "Player position x: " << playerCharacter->getPosition().x << " y: " << playerCharacter->getPosition().y << std::endl;
		cocos2d::log(s.str().c_str());
		s.clear();
		s << "Click in world position x: " << clickInWorld.x << " y: " << clickInWorld.y << std::endl;
		cocos2d::log(s.str().c_str());
		s.clear();
	}
}

Vec2 HelloWorld::GetSpriteHeading(Sprite* sprite)
{
	float rotationRad = sprite->getRotation() * PI / 180;
	return Vec2(cos(rotationRad), sin(rotationRad));
}
