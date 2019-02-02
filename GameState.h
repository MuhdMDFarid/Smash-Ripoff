#ifndef _GAME_STATE_H
#define _GAME_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "input.h"						// Inputs
#include "textureManager.h"				// Textures
#include "image.h"						// Images
#include "textDX.h"						// Fonts

class GameState
{
public:

	Game* game;

	// Abstract functions - these functions are to be used in OTHER classes (e.g. menu, game, option, etc.)
	virtual void draw() = 0;
	virtual void update(float frameTime) = 0;
	virtual void handleInput(Input* input) = 0;

	// Releasing and resetting graphic items
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};

#endif // _GAME_STATE_H