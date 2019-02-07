#include <iostream>
#include "PauseState.h"
#include "MenuState.h"
#include "game.h"

PauseState::PauseState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void PauseState::unpauseGame()
{
	// Pops up the "PauseState" (PlayState --> PauseState (popped))
	game->popState();
}

void PauseState::exitGame()
{
	// Pops everything from the list and creates a new "MenuState"
	game->deleteState();
	game->pushState(new MenuState(game));
}

void PauseState::draw()
{
	// Draws all the necessary assets
	game->pauseBackground.draw();

	game->titleFont.printC("PAUSED", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	game->buttonFont.printC("Press ESC to resume", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 2);
	game->buttonFont.printC("Press ENTER to exit", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void PauseState::update(float frameTime)
{

}

void PauseState::ai()
{

}

void PauseState::collisions()
{

}

void PauseState::handleInput(Input* input)
{
	// Keyboard
	// Unpauses the game
	if (input->isKeyDown(ESC_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ESC_KEY);
		unpauseGame();
	}

	// Exits the game (Main menu)
	else if (input->isKeyDown(ENTER_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ENTER_KEY);
		exitGame();
	}

	// Mouse
}