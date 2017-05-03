#include "Character.h"
#include "System/Libs/tinyxml2.h"
#include "GameStandart.h"
#include "System/Utils/Utils.h"
#include <Entities/Skills/Spell.h>

using namespace cocos2d;

bool Character::init(const char* pathToXML)
{
	initGraphics(pathToXML);
	setAnchorPoint(Vec2(0.5, 0.5));
	setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return mBaseSpriteFrameName.length() > 0;
}
void Character::initGraphics(const char* pathToXML)
{
	// Load the file
	tinyxml2::XMLDocument doc;
 	tinyxml2::XMLError err =  doc.LoadFile(Utils::appendFullPathToAssetsPath(pathToXML).c_str());
	if (err)
	{
		cocos2d::log("Character: XML file not found: %s", pathToXML);
	}
	tinyxml2::XMLNode* pData = doc.RootElement();

	// Parse the file
	for (tinyxml2::XMLNode* pNode = pData->FirstChildElement(); pNode;
		pNode = pNode->NextSibling())
	{
		// If we found a walk animation
		std::string nodeValue(pNode->Value());
		if (nodeValue.compare(XML_WALK_ANIM) == 0)
		{
			tinyxml2::XMLNode* pPathToSpriteSheet = pNode->FirstChild();
			tinyxml2::XMLNode* pPathToPlistFile = pPathToSpriteSheet->NextSibling();
			tinyxml2::XMLNode* pSpriteFrameName = pPathToPlistFile->NextSibling();

			// Need to use full path to assets, because all configs are Assets folder relative
			mWalkSpritebatch = SpriteBatchNode::create(Utils::appendFullPathToAssetsPath(
				pPathToSpriteSheet->FirstChild()->ToText()->Value()));
			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(Utils::appendFullPathToAssetsPath(
				pPathToPlistFile->FirstChild()->ToText()->Value()));
			
			const char* spriteFrameName = pSpriteFrameName->FirstChild()->ToText()->Value();
			char curSpriteFrameName[100] = { 0 };
			for (int i = 0; i < 8; i++)
			{
				sprintf(curSpriteFrameName, spriteFrameName, i);
				SpriteFrame* frame = spriteCache->getSpriteFrameByName(curSpriteFrameName);
				mWalkFrames.pushBack(frame);

				// Save first frame name of walk animation to use as Idle state
				if (i == 0)
				{
					mBaseSpriteFrameName = curSpriteFrameName;
				}
			}

			// init Sprite
			if (!initWithSpriteFrameName(mBaseSpriteFrameName))
			{
				cocos2d::log("Character: %s", "Sprite failed to initialize");
			}
		}
		else if (nodeValue.compare(XML_SPELL_LIST) == 0)
		{
			// Load all spells from file
			tinyxml2::XMLNode* pCurSpellNode = pNode->FirstChild();
			
			/* Need to use "do while" loop so that action comes first and then check
			 * Reason for this is that we already got the first element so we dont want
			 * to change current elemnt before we have added it to the list.			
			*/ 
			do 
			{
				addSpellElementToAvailableSpells(pCurSpellNode);

			} while (pCurSpellNode = pCurSpellNode->NextSibling());
		}
	}
}

void Character::onStartMoving(cocos2d::Vec2 clickInWorld, float timeToMove)
{
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

	// Move character and call function once movement is finished
	FiniteTimeAction* move = MoveTo::create(timeToMove, clickInWorld);
	auto moveCallBack = CallFuncN::create(CC_CALLBACK_0(Character::onCharacterMoveFinished, this));
	cocos2d::Vector<FiniteTimeAction*> allActions;
	allActions.pushBack(move);
	allActions.pushBack(moveCallBack);
	Sequence* sequence = cocos2d::Sequence::create(allActions);
	sequence->setTag(MOVE_ACTION_TAG);

	// First we stop any already runing actions
	stopActionByTag(MOVE_ACTION_TAG);
	
	// Then we start the new action
	runAction(sequence);

	// Make character face the movement direction
	float rotateAngle = Vec2::angle(forward, toClickInWorldPos) * 180 / PI * sign;
	setRotation(rotateAngle);

	// Start character animation
	auto animation = Animation::createWithSpriteFrames(mWalkFrames, 0.1f);
	auto animate = Animate::create(animation);
	auto repeatAction = RepeatForever::create(animate);
	repeatAction->setTag(WALK_ANIM_TAG);
	
	// remove any old anim action
	stopActionByTag(WALK_ANIM_TAG);
	
	// start new anim
	runAction(repeatAction);
}
void Character::onCharacterMoveFinished()
{
	stopActionByTag(WALK_ANIM_TAG);
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(mBaseSpriteFrameName));
}

// Called when player presses keyboard button for  specific spell
void Character::onShootSpell(Vec2 direction, SpellType spellType)
{
	for(unsigned int i = 0; i < mAvailableSpells.size(); i++)
	{
		Spell* currentSpell = mAvailableSpells[i];
		if(currentSpell->GetType() == spellType)
		{
			currentSpell->cast(this->getPosition(), Utils::getSpriteHeading(this));
			break;
		}
	}
}
void Character::addSpellElementToAvailableSpells(tinyxml2::XMLNode* pSpellNode)
{
	// Get the current spell element
	SpellType curSpellType = strToSpellType(pSpellNode->Value());
	if (curSpellType != None)
	{
		// Set Spell particle
		std::string pathToParticelSprite = pSpellNode->FirstChildElement(XML_PARTICLE)->
			FirstChild()->ToText()->Value();
		Sprite* particle = Sprite::create(Utils::appendFullPathToAssetsPath(
			pathToParticelSprite.c_str()));

		// Assert if particle was not initialized
		assert(particle != nullptr);

		// Set particle color
		std::string colorStr = pSpellNode->
			FirstChildElement(XML_COLOR)->FirstChild()->ToText()->Value();
		particle->setColor(Utils::stringToColor(colorStr, ","));

		// Set Spell damage
		std::string spellDmgStr = pSpellNode->
			FirstChildElement(XML_DAMAGE)->FirstChild()->ToText()->Value();

		// Set Spell range
		std::string spellRangeStr = pSpellNode->
			FirstChildElement(XML_RANGE)->FirstChild()->ToText()->Value();

		// Add Spell to available spells
		mAvailableSpells.push_back(Spell::create(curSpellType, particle,
			stof(spellDmgStr), stof(spellRangeStr)));
	}
}