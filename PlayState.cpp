#include <iostream>
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"

PlayState::PlayState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void PlayState::pausegame()
{
	// Transitions from "PlayState" to "PauseState"
	game->pushState(new PauseState(game));
}

void PlayState::draw(float frameTime)
{
	game->update();					// update all game items
	game->ai();						// aritifical intelligence (A.I.)
	game->collisions();				// handle collisions
	game->render();					// draw all game items
}

void PlayState::update(float frameTime)
{

}

void PlayState::handleInput(Input* input)
{
	// The game should pause when "ESC" is pressed
	if (input->wasKeyPressed(ESC_KEY))
		pausegame();
}