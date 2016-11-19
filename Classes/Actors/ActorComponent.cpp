#include "ActorComponent.h"

void ActorComponent::setOwner(StrongActorPtr pOwner)
{
	m_pOwner = pOwner;
}

ComponentId ActorComponent::vGetId() const 
{ 
	return Actor::getIdFromName(vGetName()); 
}