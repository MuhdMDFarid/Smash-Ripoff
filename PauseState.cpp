#include <iostream>
#include "PauseState.h"
#include "MenuState.h"

PauseState::PauseState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Initializes all the necessary assets
	if (!pauseBackgroundTexture.initialize(game->getGraphics(), PAUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause's background texture"));

	if (!pauseBackground.initialize(game->getGraphics(), 0, 0, 0, &pauseBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause's background"));

	// Initialize DirectX font
	if (!pauseFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	pauseFont.setFontColor(gameNS::FONT_COLOR);
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
	// Ideally, the game should restart here (SAFE_DELETE (game))?  
	game->pushState(new MenuState(game));
}

void PauseState::draw()
{
	// Draws all the necessary assets
	pauseBackground.draw();

	pauseFont.printC("PAUSED", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	pauseFont.printC("Press ESC to resume", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 2);
	pauseFont.printC("Press ENTER to exit", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void PauseState::update(float frameTime)
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