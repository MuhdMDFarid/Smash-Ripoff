#ifndef _GroundedState_H
#define _GroundedState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"

class GroundedState : public PlayerState
{
public:
	GroundedState();
	~GroundedState();
	PlayerState* handleInput(Player& player, Input* input /*other input*/);
	void update(Player& player,float frameTime);
	void enter(Player& player);
	void exit(Player& player);

};

#endif