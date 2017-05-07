#pragma once

#include "cocos2d.h"

enum SpellType;
class SkillPlacementHUD;
enum SkillPlacementPosition;

class CharacterHUD
{
public:
	bool init(const char* pathToXML, cocos2d::Node* pRootNode, cocos2d::Node* pUINode);
	void onMouseDown(cocos2d::Vec2 worldPosition, float delayTime);
	SpellType getSpellTypeFromPlacementPos(SkillPlacementPosition pos);
	void update(float deltaTime);

private:
	cocos2d::Sprite* m_pCurMoveTarget;
	cocos2d::Node* m_pUINode;
	SkillPlacementHUD* m_pSkillPlacementHUD;

	void onCharacterReachedWayPoint();
};
