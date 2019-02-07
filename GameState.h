#ifndef _GAME_STATE_H
#define _GAME_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "SmashRipoff.h"				// Game (SmashRipoff)
#include "input.h"						// Inputs

class GameState
{
public:

	SmashRipoff* game;

	// Abstract functions - these functions are to be used in OTHER classes (e.g. menu, game, option, etc.)
	virtual void draw() = 0;
	virtual void update(float frameTime) = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void handleInput(Input* input) = 0;

};

#endif // _GAME_STATE_H