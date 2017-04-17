#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Entities/SpellType.h"
#include "Entities/Spell.h"
#include <Libs/tinyxml2.h>

class CharAnimationComponent;

class Character: public cocos2d::Sprite
{
public:
	bool init(const char* pathToXML);
	void onStartMoving(cocos2d::Vec2 clickScreenPos, float timeToMove);
	void onShootSpell(cocos2d::Vec2 direction, SpellType spellType);

private:
	std::string mBaseSpriteFrameName;
	cocos2d::SpriteBatchNode* mWalkSpritebatch;
	cocos2d::Vector<cocos2d::SpriteFrame*> mWalkFrames;
	std::vector<Spell*> mAvailableSpells;

private:
	void initGraphics(const char* pathToXML);
	void onCharacterMoveFinished();	
	void addSpellElementToAvailableSpells(tinyxml2::XMLNode* pSpellNode);

};
