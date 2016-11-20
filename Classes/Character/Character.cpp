#include "Character.h"
#include "HelloWorldScene.h"
#include "Libs\tinyxml2.h"
#include "GameStandart.h"

using namespace cocos2d;

Character::Character()
{
}
Character::~Character()
{
}
bool Character::init(const char* pathToXML, HelloWorld* pGame)
{
	m_pGame = pGame;
	initGraphics(pathToXML);
	setAnchorPoint(Vec2(0.5, 0.5));
	setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// Set up input listeners
	auto toucheListener = EventListenerTouchOneByOne::create();
	auto mouseListener = EventListenerMouse::create();
	toucheListener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(Character::onMouseDown, this);
	pGame->addEventListenerWithSceneGraphPriority(toucheListener);
	pGame->addEventListenerWithSceneGraphPriority(mouseListener);

	return mBaseSpriteFrame != nullptr;
}
void Character::initGraphics(const char* pathToXML)
{
	// Load the file
	tinyxml2::XMLDocument doc;
	std::string absPath = "../Resources/res/";
	tinyxml2::XMLError err =  doc.LoadFile((absPath + pathToXML).c_str());
	if (err)
	{
		cocos2d::log("File not found: %s", pathToXML);
	}
	tinyxml2::XMLNode* pData = doc.RootElement();

	// Parse the file
	for (tinyxml2::XMLNode* pNode = pData->FirstChildElement(); pNode;
		pNode = pNode->NextSibling())
	{
		// If we found a walk animation
		cocos2d::String nodeValue(pNode->Value());
		if (cocos2d::String(WALK_ANIM).isEqual(&nodeValue))
		{
			tinyxml2::XMLNode* pPathToSpriteSheet = pNode->FirstChild();
			tinyxml2::XMLNode* pPathToPlistFile = pPathToSpriteSheet->NextSibling();
			mWalkSpritebatch = SpriteBatchNode::create(pPathToSpriteSheet->FirstChild()->ToText()->Value());

			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(pPathToPlistFile->FirstChild()->ToText()->Value());
			
			char str[100] = { 0 };
			for (int i = 0; i < 8; i++)
			{
				
				sprintf(str, "player-move-anim0-%d.png", i);
				SpriteFrame* frame = spriteCache->getSpriteFrameByName(str);
				mWalkFrames.pushBack(frame);
			}
		}
		// Init sprite
		else if (cocos2d::String(SPRITE_FRAME).isEqual(&nodeValue))
		{
			tinyxml2::XMLNode* pPathToSprite = pNode->FirstChild();
			tinyxml2::XMLNode* pSpriteFrameRect = pPathToSprite->NextSibling();
			std::vector<float> rectValues = stringToVector(
				pSpriteFrameRect->FirstChild()->ToText()->Value());
			
			if (rectValues.size() > 3)
			{
				mBaseSpriteFrame = cocos2d::SpriteFrame::create(
					pPathToSprite->FirstChild()->ToText()->Value(),
					Rect(rectValues[0], rectValues[1], rectValues[2], rectValues[3]));
				initWithSpriteFrame(mBaseSpriteFrame);
			}
			else
			{
				cocos2d::log("Character: %s", "Invalid rect defined in the XML!");
			}

		}
	}
}
Vec2 Character::getSpriteHeading(Sprite* sprite)
{
	Vec2 playerPos = getPosition();
	float rotationRad = sprite->getRotation() * PI / 180;
	return Vec2(playerPos.x + (rotationRad), playerPos.y + (rotationRad));
}
Vec2 Character::getTouchInWorldPosition(Vec2 screenPos)
{
	Vec2 playerCharPos = getPosition();
	return Vec2(playerCharPos.x + (screenPos.x - (SCREEN_WIDTH / 2)),
		playerCharPos.y + ((screenPos.y - (SCREEN_HEIGHT / 2)) * (-1)));
}
std::vector<float> Character::stringToVector(cocos2d::String str)
{
	const char* cStr = str.getCString();
	std::vector<float> numbers;
	int rectIdx = 0;

	for (int index = 0; index < str.length(); index++)
	{
		if (cStr[index] != ']' && cStr[index] != '[')
		{
			// Reads the whole number
			std::string wholeNumber = "";
			while (cStr[index] != ',' && cStr[index] != ']')
			{
				wholeNumber += cStr[index];
				index++;
			}

			// Transforms numbers in string format to integer format
			numbers.push_back(atof(wholeNumber.c_str()));
			rectIdx++;
		}
	}
	return numbers;
}
void Character::onTouchEnded(Touch* touch, Event* event)
{
}
void Character::onMouseDown(cocos2d::Event* event)
{
	// Get the main camera to make it fallow the player
	Camera* camera = Camera::getDefaultCamera();

	// Before creating new player action remove previous one
	m_pGame->getRootNode()->getActionManager()->removeAllActionsByTag(MOVE_ACTION_TAG, this);
	m_pGame->getRootNode()->getActionManager()->removeAllActionsByTag(MOVE_ACTION_TAG, camera);

	// Cauculate new position and rotation
	EventMouse* e = (EventMouse*)event;
	Vec2 clickInWorld = getTouchInWorldPosition(e->getLocation());
	float distanceToTravel = getPosition().distance(clickInWorld);
	float movementSpeed = distanceToTravel / 50;
	FiniteTimeAction* move = MoveTo::create(movementSpeed, clickInWorld);
	move->setTag(MOVE_ACTION_TAG);

	Vec2 forward(0, 1);
	Vec2 toClickInWorldPos = clickInWorld - getPosition();
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

	setRotation(rotateAngle);
	runAction(sequence);

	// Move camera
	Action* moveCamera = MoveTo::create(movementSpeed, Vec3(clickInWorld.x, clickInWorld.y,
		camera->getPosition3D().z));
	moveCamera->setTag(MOVE_ACTION_TAG);
	camera->runAction(moveCamera);

	// Start animation
	auto animation = Animation::createWithSpriteFrames(mWalkFrames, 0.1f);
	auto animate = Animate::create(animation);
	auto repeatAction = RepeatForever::create(animate);
	repeatAction->setTag(WALK_ANIM_TAG);
	runAction(repeatAction);
}
void Character::onCharacterMoveFinished()
{
	stopActionByTag(WALK_ANIM_TAG);
	//setSpriteFrame(mBaseSpriteFrame);
}