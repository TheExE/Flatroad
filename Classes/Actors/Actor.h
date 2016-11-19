#pragma once
#include "cocos2d.h"
#include "Libs/tinyxml2.h"
#include "GameStandart.h"

class HelloWorld;

class Actor
{
	friend class ActorFactory;
	typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;

	ActorId mId;
	ActorComponents mComponents;

public:
	Actor();
	~Actor();

	virtual const char* vGetName() const = 0;
	static ComponentId getIdFromName(const char* compName);
	
	bool init(tinyxml2::XMLNode* pData, HelloWorld* pGame);
	virtual void postInit();
	void destroy();
	void update(float deltaTime);

	// Accessors
	ActorId GetId() const;

	// Template for retrieving components
	template <class ComponentType>
	std::weak_ptr<ComponentType> getComponent(ComponentId id)
	{
		ActorComponents::iterator findComp = mComponents.find(id);
		if (findComp != mComponents.end())
		{
			StrongActorComponentPtr pBase(findComp->second);
			//cast to subclass version of the pointer
			std::shared_ptr<ComponentType> pSub(
				std::tr1::static_pointer_cast<ComponentType>(pBase));
			std::weak_ptr<ComponentType> pWeakSub(pSub); // convert strong pointer to weak

			return pWeakSub;
		}
		else
		{
			return std::weak_ptr<ComponentType>();
		}
	}
protected:
	HelloWorld* pGame;

private:
	// This is called by the ActorFactory; no one else should be
	// adding components
	void addComponent(StrongActorComponentPtr pComponent);

};