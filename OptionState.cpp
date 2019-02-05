#include <iostream>
#include "OptionState.h"

OptionState::OptionState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Initializes all the necessary assets
	if (!optionBackgroundTexture.initialize(game->getGraphics(), OPTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing option's background texture"));

	if (!optionBackground.initialize(game->getGraphics(), 0, 0, 0, &optionBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing option's background"));

	// Initialize DirectX font
	if (!optionFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	optionFont.setFontColor(gameNS::FONT_COLOR);
}

OptionState::~OptionState()
{
	// Call onLostDevice for all graphic items
	releaseAll();
}

void OptionState::exitOption()
{
	// Transitions from "OptionState" to "MenuState"
	game->popState();
}

void OptionState::draw()
{
	// Draws all the necessary assets
	optionBackground.draw();

	optionFont.printC("Press ESC to leave", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 2);
}

void OptionState::update(float frameTime)
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

void OptionState::releaseAll()
{
	optionBackgroundTexture.onLostDevice();
	game->releaseAll();
	return;
}

void OptionState::resetAll()
{
	optionBackgroundTexture.onResetDevice();
	game->resetAll();
	return;
}