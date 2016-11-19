#include "Actor.h"
#include "ActorComponent.h"
#include "Utils/HashString.h"
#include "HelloWorldScene.h"

Actor::Actor()
{
	cocos2d::log("Actor: Creating Actor %d", mId);
}
Actor::~Actor(void)
{
	cocos2d::log("Actor: Destroying Actor %d", mId);
}

ActorId Actor::GetId() const
{
	return mId;
}

bool Actor::init(tinyxml2::XMLNode* pData, HelloWorld* pGame)
{
	cocos2d::log("Actor: Initializing Actor %d",mId);
	this->pGame = pGame;

	return true;
}

void Actor::postInit(void)
{
	for (ActorComponents::iterator it = mComponents.begin(); it != mComponents.end();
		++it)
	{
		it->second->vPostInit();
	}
}

void Actor::destroy(void)
{
	mComponents.clear();
}

void Actor::update(float deltaTime)
{
	for (ActorComponents::iterator it = mComponents.begin(); it != mComponents.end();
		++it)
	{
		it->second->vUpdate(deltaTime);
	}
}
void Actor::addComponent(StrongActorComponentPtr pComponent)
{
	mComponents.insert(std::make_pair(pComponent->vGetId(), pComponent));
}
ComponentId Actor::getIdFromName(const char* compName)
{
	void* rawId = HashedString::hash_name(compName);
	return reinterpret_cast<ComponentId>(rawId);
}