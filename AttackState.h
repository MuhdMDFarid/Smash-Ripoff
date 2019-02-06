#ifndef _AttackState_H
#define _AttackState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"
class AttackState :	public PlayerState
{
public:
	AttackState();
	~AttackState();
	PlayerState* handleInput(Player& player,Input* input /*other input*/);
	void update(Player& player, float frameTime);
	void enter(Player& player);
	void exit(Player& player);
	void interrupt(Player& player);
};

#endif