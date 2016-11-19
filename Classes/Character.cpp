#include "Character.h"
#include "Actors/SpriteComponent.h"
#include "Actors/CharAnimationComponent.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

const char* Character::gName = "CharacterActor";

Character::Character()
	:
	Actor()
{
}
Character::~Character()
{

}
void Character::postInit()
{
	// Get references to necessary components
	std::weak_ptr<SpriteComponent> spriteComp = getComponent<SpriteComponent>(
		Actor::getIdFromName(SpriteComponent::gName));
	mCharSprite = spriteComp.lock().get()->getSprite();
	pGame->getRootNode()->addChild(mCharSprite);
	
	mAnimationComp = getComponent<CharAnimationComponent>(
		Actor::getIdFromName(CharAnimationComponent::gName)).lock();
	

	// Set up intpu listeners
	auto toucheListener = EventListenerTouchOneByOne::create();
	auto mouseListener = EventListenerMouse::create();
	toucheListener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(Character::onMouseDown, this);

	// Add listener
	pGame->addEventListenerWithSceneGraphPriority(toucheListener);
	pGame->addEventListenerWithSceneGraphPriority(mouseListener);
}

void Character::onTouchEnded(Touch* touch, Event* event)
{
}
void Character::onMouseDown(cocos2d::Event* event)
{
	// Get the main camera to make it fallow the player
	Camera* camera = Camera::getDefaultCamera();

	// Before creating new player action remove previous one
	pGame->getRootNode()->getActionManager()->removeAllActionsByTag(MOVE_ACTION_TAG, mCharSprite);
	pGame->getRootNode()->getActionManager()->removeAllActionsByTag(MOVE_ACTION_TAG, camera);

	// Cauculate new position and rotation
	EventMouse* e = (EventMouse*)event;
	Vec2 clickInWorld = getTouchInWorldPosition(e->getLocation());
	float distanceToTravel = mCharSprite->getPosition().distance(clickInWorld);
	float movementSpeed = distanceToTravel / 50;
	FiniteTimeAction* move = MoveTo::create(movementSpeed, clickInWorld);
	move->setTag(MOVE_ACTION_TAG);

	Vec2 forward(0, 1);
	Vec2 toClickInWorldPos = clickInWorld - mCharSprite->getPosition();
	Vec2 right(1, 0);

	int sign = 0;
	if (Vec2::dot(right, toClickInWorldPos) > 0)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	/*
	Since angle uses dot product it only can show angles up to 180 degrees
	this is why we use another dot product to determine the direction of rotation.
	And we determine the direction of rotation by peforming dot product on vector
	to the right of the character and vector from character  to click in world space.
	If dot product is positive then both vectors are on same side in this case to the right
	of the character, but if the dot product is negative then the vectors are on different
	sides in this case one is on right side and the other on left. This is how we can
	distinguish between rotation directions.
	*/
	float rotateAngle = Vec2::angle(forward, toClickInWorldPos) * 180 / PI * sign;

	// Move character and call function once movement is finished
	auto moveCallBack = CallFuncN::create(CC_CALLBACK_0(Character::onCharacterMoveFinished, this));
	cocos2d::Vector<FiniteTimeAction*> allActions;
	allActions.pushBack(move);
	allActions.pushBack(moveCallBack);
	Sequence* sequence = cocos2d::Sequence::create(allActions);

	mCharSprite->setRotation(rotateAngle);
	mCharSprite->runAction(sequence);

	// Move camera
	Action* moveCamera = MoveTo::create(movementSpeed, Vec3(clickInWorld.x, clickInWorld.y,
		camera->getPosition3D().z));
	moveCamera->setTag(MOVE_ACTION_TAG);
	camera->runAction(moveCamera);

	// Start animation
	mAnimationComp->playWalkAnimation(mCharSprite);
}
Vec2 Character::getSpriteHeading(Sprite* sprite)
{
	Vec2 playerPos = mCharSprite->getPosition();
	float rotationRad = sprite->getRotation() * PI / 180;
	return Vec2(playerPos.x + (rotationRad), playerPos.y + (rotationRad));
}
Vec2 Character::getTouchInWorldPosition(Vec2 screenPos)
{
	Vec2 playerCharPos = mCharSprite->getPosition();
	return Vec2(playerCharPos.x + (screenPos.x - (SCREEN_WIDTH / 2)),
		playerCharPos.y + ((screenPos.y - (SCREEN_HEIGHT / 2)) * (-1)));
}
void Character::onCharacterMoveFinished()
{
	mAnimationComp->stopWalkAnimation(mCharSprite);
}