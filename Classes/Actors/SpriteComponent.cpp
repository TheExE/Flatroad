#include "SpriteComponent.h"
#include "Actors/ActorFactory.h"

const char* SpriteComponent::gName = "SpriteComponent";

bool SpriteComponent::vInit(tinyxml2::XMLNode* pData)
{
	for (tinyxml2::XMLNode* pNode = pData->FirstChildElement(); pNode;
		pNode = pNode->NextSibling())
	{
		// If sprite component has a file source
		cocos2d::String nodeValue = pNode->Value();
		if (nodeValue.isEqual(&cocos2d::String(FILE_SOURCE)))
		{
			// Then load all animation frames
			spriteToDraw = cocos2d::Sprite::create(
				pNode->FirstChild()->ToText()->Value());
			spriteToDraw->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		}
		else if (nodeValue.isEqual(&cocos2d::String(SPRITE_POS)))
		{
			std::vector<float> vect = ActorFactory::stringToVector(
				cocos2d::String(pNode->FirstChild()->ToText()->Value()));
			spriteToDraw->setPosition(vect[0], vect[1]);
		}
	}
	
	return true;
}

void SpriteComponent::vUpdate(float deltaTime)
{

}

cocos2d::Sprite* SpriteComponent::getSprite() const
{
	return spriteToDraw;
}