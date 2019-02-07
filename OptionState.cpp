#include <iostream>
#include "OptionState.h"

OptionState::OptionState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void OptionState::exitOption()
{
	// Transitions from "OptionState" to "MenuState"
	game->popState();
}

void OptionState::draw()
{
	// Draws all the necessary assets
	game->optionBackground.draw();

	game->titleFont.printC("Press ESC to leave", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 2);
}

void OptionState::update(float frameTime)
{

}

void OptionState::ai()
{

}

void OptionState::collisions()
{

}

void OptionState::handleInput(Input* input)
{
	// Keyboard
	// Leaves the option menu
	if (input->isKeyDown(ESC_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ESC_KEY);
		exitOption();
	}

	// Mouse
}