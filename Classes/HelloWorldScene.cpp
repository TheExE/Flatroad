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

	if (!Layer::init())
	{
		return false;
	}
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
	playerCharacter->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	auto rootNode = CSLoader::createNode("MainScene.csb");
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
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
	// Get the main camera to make it fallow the player
	Camera* camera = Camera::getDefaultCamera();

	// Before creating new player action remove previous one
	getActionManager()->removeAllActionsByTag(MOVE_ACTION_TAG, playerCharacter);
	getActionManager()->removeAllActionsByTag(MOVE_ACTION_TAG, camera);
	
	// Cauculate new position and rotation
	EventMouse* e = (EventMouse*)event;
	Vec2 clickInWorld = GetTouchInWorldPosition(e->getLocation());
	float distanceToTravel = playerCharacter->getPosition().distance(clickInWorld);
	float movementSpeed = distanceToTravel / 50;
	Action* move = MoveTo::create(movementSpeed, clickInWorld);
	move->setTag(MOVE_ACTION_TAG);
	
	Vec2 forward(0, 1);
	Vec2 toClickInWorldPos = clickInWorld - playerCharacter->getPosition();

	int sign = 0;
	if (toClickInWorldPos.x > 0)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	float rotateAngle = Vec2::angle(forward, toClickInWorldPos) * 180 / PI * sign;
	
	// Move character
	playerCharacter->runAction(move);
	playerCharacter->setRotation(rotateAngle);

	// Move camera
	Action* moveCamera = MoveTo::create(movementSpeed, Vec3(clickInWorld.x, clickInWorld.y,
		camera->getPosition3D().z));
	moveCamera->setTag(MOVE_ACTION_TAG);
	camera->runAction(moveCamera);

	
	std::stringstream s;
	s << "Angle:  " << rotateAngle << std::endl;
	cocos2d::log(s.str().c_str());
	s.clear();

	s << "To click in world pos x: " << toClickInWorldPos.x << " y: " << toClickInWorldPos.y << std::endl;
	cocos2d::log(s.str().c_str());
	s.clear();

}

Vec2 HelloWorld::GetSpriteHeading(Sprite* sprite)
{
	Vec2 playerPos = playerCharacter->getPosition();
	float rotationRad = sprite->getRotation() * PI / 180;
	return Vec2(playerPos.x + (rotationRad), playerPos.y + (rotationRad));
}
Vec2 HelloWorld::GetTouchInWorldPosition(Vec2 screenPos)
{
	Vec2 playerCharPos = playerCharacter->getPosition();
	return Vec2(playerCharPos.x + (screenPos.x - (SCREEN_WIDTH / 2)),
		playerCharPos.y + ((screenPos.y - (SCREEN_HEIGHT / 2)) * (-1)));
}