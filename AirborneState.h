#ifndef _AirborneState_H
#define _AirborneState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"

class AirborneState : public PlayerState
{
public:
	AirborneState();
	~AirborneState();
	PlayerState* handleInput(Player& player, Input* input /*other input*/);
	void update(Player& player, float frameTime);
	void enter(Player& player);
	void exit(Player& player);
};

#endif