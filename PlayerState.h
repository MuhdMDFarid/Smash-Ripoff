#ifndef  _PlayerState_H
#define _PlayerState_H
#define WIN32_LEAN_AND_MEAN

#include "Player.h"
#include "constants.h"


class PlayerState
{
private:

	//Player* player;

public:
	PlayerState();
	~PlayerState();
	virtual PlayerState* handleInput(Player& player, Input* input /*other input*/) = 0;
	virtual void update(Player& player, float frameTime) = 0;
	virtual void enter(Player& player) = 0;
	virtual void exit(Player& player) = 0;
};

#endif