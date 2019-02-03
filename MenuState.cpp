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

MenuState::~MenuState()
{
	// Call onLostDevice for all graphic items
	releaseAll();
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
	// The game is exited if "ESC" is pressed
	if (input->isKeyDown(ESC_KEY))
		game->exitGame();

	// The game starts if "ENTER" is pressed
	else if (input->isKeyDown(ENTER_KEY))
		startGame();

	// The game moves to the options if "V" is pressed
	else if (input->isKeyDown(V_KEY))
		optionsMenu();
	// Mouse
}

void MenuState::releaseAll()
{
	menuBackgroundTexture.onLostDevice();
	game->releaseAll();
	return;
}

void MenuState::resetAll()
{
	menuBackgroundTexture.onResetDevice();
	game->resetAll();
	return;
}