#ifndef _IdleState_H
#define _IdleState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"

class IdleState : public PlayerState
{
public:
	IdleState();
	~IdleState();
	PlayerState* handleInput(Player& player, Input* input /*other input*/);
	void update(Player& player, float frameTime);
	void enter(Player& player);
	void exit(Player& player);
	void interrupt(Player& player);
};

#endif