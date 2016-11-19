#include "CharAnimationComponent.h"
#include "Actors/ActorFactory.h"

const char* CharAnimationComponent::gName = "CharAnimationComponent";

bool CharAnimationComponent::vInit(tinyxml2::XMLNode* pData)
{	
	for (tinyxml2::XMLNode* pNode = pData->FirstChildElement(); pNode;
		pNode = pNode->NextSibling())
	{
		// If we found and walk animation
		cocos2d::String nodeValue(pNode->Value());
		if (cocos2d::String(WALK_ANIM).isEqual(&nodeValue))
		{
			// If it has a sprite sheet
			tinyxml2::XMLNode* spriteSheetNode = pNode->FirstChildElement();
			nodeValue = spriteSheetNode->Value();
			if (nodeValue.isEqual(&cocos2d::String(SPRITE_SHEET)))
			{
				// If it has a file source
				tinyxml2::XMLNode* spriteSheetChild = spriteSheetNode->FirstChildElement();
				nodeValue = spriteSheetChild->Value();
				if (nodeValue.isEqual(&cocos2d::String(FILE_SOURCE)))
				{
					// Then load all animation frames
					cocos2d::Sprite* walkAnim = cocos2d::Sprite::create( 
								spriteSheetChild->FirstChild()->ToText()->Value());
					cocos2d::Vector<cocos2d::SpriteFrame*> walkAnimFrames;
					int frameNumber = 1;
					// While there is next frame
					while (spriteSheetChild = spriteSheetChild->NextSibling())
					{
						nodeValue = spriteSheetChild->Value();
						cocos2d::String animFrame(ANIM_FRAME);
						animFrame.appendWithFormat("%d", frameNumber);
						// If next frame is found
						if (nodeValue.isEqual(&animFrame))
						{
							cocos2d::SpriteFrame* frame = cocos2d::SpriteFrame::createWithTexture(
										walkAnim->getTexture(),
								stringToRect(cocos2d::
									String(spriteSheetChild->FirstChild()->ToText()->Value())));
							walkAnimFrames.pushBack(frame);
							frameNumber++;
						}
					}
					walkFrames.push_back(walkAnimFrames);
				}
			}
		}
	}
	return true;
}
void CharAnimationComponent::vUpdate(float deltaTime)
{

}
cocos2d::Rect CharAnimationComponent::stringToRect(cocos2d::String str)
{
	std::vector<float> numbers = ActorFactory::stringToVector(str);
	return cocos2d::Rect(numbers[0], numbers[1], numbers[2], numbers[3]);
}
void CharAnimationComponent::playWalkAnimation(cocos2d::Sprite* keySprite)
{
	if (walkFrames.size() > 0)
	{
		walkAnim = cocos2d::Animation::createWithSpriteFrames(walkFrames[0], 0.1f);
		animate = cocos2d::Animate::create(walkAnim);
		animate->setTag(WALK_ANIM_TAG);
		keySprite->runAction(animate);
	}
}
void CharAnimationComponent::stopWalkAnimation(cocos2d::Sprite* keySprite)
{
	keySprite->stopActionByTag(WALK_ANIM_TAG);
}