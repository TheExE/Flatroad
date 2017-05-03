#include "StateMachine.h"
#include "State.h"
#include "WanderState.h"

StateMachine::StateMachine()
{
	m_pOwner = NULL;
	m_pCurState = NULL;
}
StateMachine::~StateMachine()
{
}
bool StateMachine::init(Enemy* pOwner) 
{
	m_pOwner = pOwner;
	switchState(new WanderState());

	return pOwner != NULL;
}
void StateMachine::switchState(State* pNewState)
{
	if (m_pCurState != NULL)
	{
		m_pCurState->onExit();
	}
	pNewState->onEnter(m_pOwner);
	m_pCurState = pNewState;
}
void StateMachine::update(float deltaTime)
{
	m_pCurState->onUpdate(deltaTime);
}