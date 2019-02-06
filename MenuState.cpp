#include <iostream>
#include "MenuState.h"
#include "PlayState.h"
#include "OptionState.h"

MenuState::MenuState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Initializes all the necessary assets
	if (!menuBackgroundTexture.initialize(game->getGraphics(), MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu's background texture"));

	if (!menuBackground.initialize(game->getGraphics(), 0, 0, 0, &menuBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu's background"));

	// Initialize DirectX font
	if (!menuFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	menuFont.setFontColor(gameNS::FONT_COLOR);
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
	menuBackground.draw();

	menuFont.printC("Main Menu", GAME_WIDTH / 2, GAME_HEIGHT / 5);
	menuFont.printC("Press ENTER to continue", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 2);
	menuFont.printC("Press V for Options", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 3);
	menuFont.printC("Press ESC to leave", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 4);
}

void MenuState::update(float frameTime)
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