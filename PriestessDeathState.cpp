#include <iostream>
#include "PriestessDeathState.h"
#include "MenuState.h"

PriestessDeathState::PriestessDeathState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Initializes all the necessary assets
	if (!priestessDeathTexture.initialize(game->getGraphics(), PRIESTESS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing priestess's background texture"));

	if (!priestessBackground.initialize(game->getGraphics(), 0, 0, 0, &priestessDeathTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing priestess's background"));

	// Initialize the DirectX font
	if (!priestessFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// Set the DirectX font color
	priestessFont.setFontColor(gameNS::FONT_COLOR);
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
	priestessBackground.draw();

	priestessFont.printC("Hunter Wins!!", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	priestessFont.printC("Press <enter> to return", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void PriestessDeathState::update(float frameTime)
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