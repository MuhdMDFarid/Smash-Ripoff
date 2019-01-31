#include <iostream>
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"

// Just testing purposes
#include "textDX.h"

MenuState::MenuState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void MenuState::startgame()
{
	// Transitions from "MenuState" to "PlayState"
	game->pushState(new PlayState(game));
}

void MenuState::draw(float frameTime)
{
	TextDX dxFont;	// Testing

	if (dxFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	dxFont.setFontColor(gameNS::FONT_COLOR);
	dxFont.printC("Main Menu", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	dxFont.printC("Press ENTER to continue", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 2);
	dxFont.printC("Press ESC to leave", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void MenuState::update(float frameTime)
{

}

void MenuState::handleInput(Input* input)
{
	// Testing purposes (ideally you would use your mouse)
	// The game is exited if "ESC" is pressed
	if (input->isKeyDown(ESC_KEY))
		game->exitGame();

	else if (input->isKeyDown(ENTER_KEY))
		startgame();
}