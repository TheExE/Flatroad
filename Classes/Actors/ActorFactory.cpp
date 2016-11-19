#include "ActorFactory.h"
#include "CharAnimationComponent.h"
#include "SpriteComponent.h"
#include "GameStandart.h"
#include "Character.h"

ActorFactory::ActorFactory() 
{
	mLastActorId = INVALID_ACTOR_ID;
	mComponentFactory.
		registerObj<CharAnimationComponent>(
			Actor::getIdFromName(CharAnimationComponent::gName));
	mComponentFactory.
		registerObj<SpriteComponent>(Actor::getIdFromName(SpriteComponent::gName));

	mActorCreatorMap.registerObj<Character>(Actor::getIdFromName(Character::gName));
}
StrongActorPtr ActorFactory::createActor(const char* actorResource, HelloWorld* pGame)
{
	// Grab the root XML node
	tinyxml2::XMLDocument doc; 
	cocos2d::String path("../Resources/res/");
	path.append(actorResource);
	tinyxml2::XMLError err = doc.LoadFile(path.getCString());
	if (err)
	{
		cocos2d::log((const char*)err);
	}

	tinyxml2::XMLNode* pRoot = doc.RootElement();
	if (!pRoot)
	{
		cocos2d::log("Failed to create actor from xml!");
		return StrongActorPtr();
	}

	// Create the actor instance
	StrongActorPtr pActor(mActorCreatorMap.create(Actor::getIdFromName(Character::gName)));
	if (!pActor->init(pRoot, pGame))
	{
		cocos2d::log("Failed to initialize actor %s", actorResource);
		return StrongActorPtr();
	}

	// Loop through each child element and load the component
	for (tinyxml2::XMLNode* pNode = pRoot->FirstChildElement(); pNode;
		pNode = pNode->NextSiblingElement())
	{
		StrongActorComponentPtr pComponent(createComponent(pNode));
		if (pComponent)
		{
			pActor->addComponent(pComponent);
			pComponent->setOwner(pActor);
		}
		else
		{
			return StrongActorPtr();
		}
	}

	// After actor has been fully loaded run post init phase
	pActor->postInit();

	return pActor;
}
StrongActorComponentPtr ActorFactory::createComponent(tinyxml2::XMLNode* pData)
{
	const char* name = pData->Value();
	StrongActorComponentPtr pComponent(mComponentFactory.
		create(Actor::getIdFromName(name)));

	if (pComponent)
	{
		if (!pComponent->vInit(pData))
		{
			cocos2d::log("Failed to init component!");
			return StrongActorComponentPtr();
		}
	}

	else
	{
		cocos2d::log("Could not find actor component named: %s", name);
		return StrongActorComponentPtr();
	}

	// pComponent will be NULL if the compoennt wasn't found. This isn't
	// necessary an error since you might have a custom CreateComponent()
	// function in a subclass

	return pComponent;
}
ActorId ActorFactory::getNextActorId()
{
	return ++mLastActorId;
}
std::vector<float> ActorFactory::stringToVector(cocos2d::String str)
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