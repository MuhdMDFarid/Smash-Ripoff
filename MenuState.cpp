#include <iostream>
#include "MenuState.h"
#include "PlayState.h"
#include "OptionState.h"

MenuState::MenuState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void MenuState::startGame()
{
	// Transitions from "MenuState" to "PlayState"
	game->pushState(new PlayState(game));
}

void MenuState::optionsMenu()
{
	// Transitions from "MenuState" to "OptionState"
	game->pushState(new OptionState(game));
}

void MenuState::draw()
{
	// Draws all the necessary assets
	game->menuBackground.draw();

	game->titleFont.printC("Main Menu", GAME_WIDTH / 2, GAME_HEIGHT / 5);
	game->buttonFont.printC("Press ENTER to continue", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 2);
	game->buttonFont.printC("Press V for Options", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 3);
	game->buttonFont.printC("Press ESC to leave", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 4);
}

void MenuState::update(float frameTime)
{

}

void MenuState::ai()
{

}

void MenuState::collisions()
{

}

void MenuState::handleInput(Input* input)
{
	// Keyboard
	// Exits the game
	if (input->isKeyDown(ESC_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ESC_KEY);
		game->exitGame();

	}

	// Starts the game
	else if (input->isKeyDown(ENTER_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ENTER_KEY);
		startGame();
	}

	// Opens up the options menu
	else if (input->isKeyDown(V_KEY))
	{
		optionsMenu();
	}
	
	// Mouse
}