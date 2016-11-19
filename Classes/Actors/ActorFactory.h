#pragma once
#include "cocos2d.h"
#include "Libs\tinyxml2.h"
#include "GameStandart.h"


template <class BaseType, class SubType>
BaseType* GenericObjectCreationFunction(void) { return new SubType; }

template <class BaseClass, class IdType>
class GenericObjectFactory
{
	typedef BaseClass* (*ObjectCreationFunction)(void);
	std::map<IdType, ObjectCreationFunction> m_creationFunctions;

public:
	template <class SubClass>
	bool registerObj(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt == m_creationFunctions.end())
		{
			m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;  // insert() is giving me compiler errors
			return true;
		}

		return false;
	}

	BaseClass* create(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt != m_creationFunctions.end())
		{
			ObjectCreationFunction pFunc = findIt->second;
			return pFunc();
		}

		return NULL;
	}
};

class HelloWorld;

class ActorFactory
{
private:
	ActorId mLastActorId;

protected:
	GenericObjectFactory<ActorComponent, ComponentId> mComponentFactory;
	GenericObjectFactory<Actor, ActorId> mActorCreatorMap;

public:
	ActorFactory();
	StrongActorPtr createActor(const char* actorResource, HelloWorld* pGame);
	static std::vector<float> stringToVector(cocos2d::String str);

protected:
	virtual StrongActorComponentPtr createComponent(tinyxml2::XMLNode* pData);

private:
	ActorId getNextActorId();

};