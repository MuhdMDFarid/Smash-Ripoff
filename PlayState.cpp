#include <iostream>
#include "PlayState.h"
#include "PauseState.h"

PlayState::PlayState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

PlayState::~PlayState()
{
	// Isn't needed because it got released in SmashRipoff.cpp
}

void PlayState::pauseGame()
{
	// Transitions from "PlayState" to "PauseState"
	game->pushState(new PauseState(game));
}

void PlayState::draw()
{
	game->render();					// Draw all game items
}

void PlayState::update(float frameTime)
{
	game->update();					// Update all game items
	game->ai();						// Aritifical Intelligence (A.I.)
	game->collisions();				// Handle collisions
}

void PlayState::handleInput(Input* input)
{
	// Keyboard
	// Pauses the game
	if (input->isKeyDown(ESC_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ESC_KEY);
		pauseGame();
	}

	// Mouse
}

void PlayState::releaseAll()
{
	// Isn't needed because it got released in SmashRipoff.cpp
}

void PlayState::resetAll()
{
	// Isn't needed because it got released in SmashRipoff.cpp
}