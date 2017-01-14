#pragma once

class State;
class Enemy;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	bool init(Enemy* pOwner);
	void update(float deltaTime);
	void switchState(State* pNewState);

private:
	State* m_pCurState;
	Enemy* m_pOwner;
};