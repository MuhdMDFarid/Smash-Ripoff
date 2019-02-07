#include <iostream>
#include "HunterDeathState.h"
#include "MenuState.h"

#include "SmashRipoff.h" // This is really bad but I'm just testing

HunterDeathState::HunterDeathState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Initializes all the necessary assets
	if (!hunterDeathTexture.initialize(game->getGraphics(), HUNTER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hunter's background texture"));

	if (!hunterBackground.initialize(game->getGraphics(), 0, 0, 0, &hunterDeathTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hunter's background"));

	// Initialize the DirectX font
	if (!hunterFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	
	// Set the DirectX font color
	hunterFont.setFontColor(gameNS::FONT_COLOR);
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
	hunterBackground.draw();

	hunterFont.printC("Priestess Wins!!", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	hunterFont.printC("Press <enter> to return", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void HunterDeathState::update(float frameTime)
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