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
	game->update();					// Update all game items
	game->ai();						// Aritifical Intelligence (A.I.)
	game->collisions();				// Handle collisions
	game->render();					// Draw all game items
}

void PlayState::update(float frameTime)
{

}

void PlayState::handleInput(Input* input)
{
	// Keyboard
	// The game should pause when "ESC" is pressed
	if (input->isKeyDown(ESC_KEY))
		pauseGame();

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