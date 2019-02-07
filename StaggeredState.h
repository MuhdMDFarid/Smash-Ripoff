#ifndef _StaggeredState_H
#define _StaggeredState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"
#include "IdleState.h"

class StaggeredState : public PlayerState
{
private:
	float duration;
public:
	StaggeredState();
	StaggeredState(float stunduration);
	~StaggeredState();
	PlayerState* handleInput(Player& player, Input* input /*other input*/);
	void update(Player& player, float frameTime);
	void enter(Player& player);
	void exit(Player& player);
	PlayerState* interrupt(Player& player,float stunduration);
	void recover(Player& player);
};

#endif