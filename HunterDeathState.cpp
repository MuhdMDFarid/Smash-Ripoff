#include <iostream>
#include "HunterDeathState.h"
#include "MenuState.h"

HunterDeathState::HunterDeathState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void HunterDeathState::mainMenu()
{
	// Pops everything from the list and creates a new "MenuState"
	game->deleteState();
	game->pushState(new MenuState(game));
}

void HunterDeathState::draw()
{
	// Draws all the necessary assets
	game->hunterBackground.draw();

	game->titleFont.printC("Priestess Wins!!", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	game->buttonFont.printC("Press <enter> to return", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void HunterDeathState::update(float frameTime)
{

}

void HunterDeathState::ai()
{

}

void HunterDeathState::collisions()
{

}

void HunterDeathState::handleInput(Input* input)
{
	// Keyboard
	// Returns to the menu
	if (input->isKeyDown(ENTER_KEY))
	{
		input->keyUp(ENTER_KEY);
		mainMenu();
	}
}