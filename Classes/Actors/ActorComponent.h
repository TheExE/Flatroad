#pragma once
#include "Actor.h"

class ActorComponent
{
	friend class ActorFactory;

protected:
	StrongActorPtr m_pOwner;

public:
	virtual ~ActorComponent() {}

	// These functions are meant to be overridden by the implementation
	// classes of the components.
	virtual bool vInit(tinyxml2::XMLNode* pData) = 0;
	virtual void vPostInit() {}
	virtual void vUpdate(float deltaTime) {}

	// This function should be overriden by the interface class.
	virtual ComponentId vGetId(void) const;
	virtual const char* vGetName() const = 0;

private:
	void setOwner(StrongActorPtr pOwner);

};