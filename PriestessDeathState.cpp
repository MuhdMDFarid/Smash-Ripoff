#include <iostream>
#include "PriestessDeathState.h"
#include "MenuState.h"

PriestessDeathState::PriestessDeathState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void PriestessDeathState::mainMenu()
{
	// Pops everything from the list and creates a new "MenuState"
	game->deleteState();
	game->pushState(new MenuState(game));
}

void PriestessDeathState::draw()
{
	// Draws all necessary assets
	game->priestessBackground.draw();

	game->titleFont.printC("Hunter Wins!!", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	game->buttonFont.printC("Press <enter> to return", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void PriestessDeathState::update(float frameTime)
{

}

void PriestessDeathState::ai()
{

}

void PriestessDeathState::collisions()
{

}

void PriestessDeathState::handleInput(Input* input)
{
	// Keyboard
	// Returns to the menu
	if (input->isKeyDown(ENTER_KEY))
	{
		input->keyUp(ENTER_KEY);
		mainMenu();
	}
}