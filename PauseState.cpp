#include <iostream>
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"

// Just testing purposes
#include "textDX.h"

PauseState::PauseState(Game* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void PauseState::unpausegame()
{
	// Pops up the "PauseState" (PlayState --> PauseState (popped))
	game->popState();
}

void PauseState::exitgame()
{
	// Pops everything from the list and creates a new "MenuState"
	game->deleteState();
	game->pushState(new MenuState(game));
}

void PauseState::draw(float frameTime)
{
	TextDX dxFont;	// Testing

	if (dxFont.initialize(game->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	dxFont.setFontColor(gameNS::FONT_COLOR);
	dxFont.printC("PAUSED", GAME_WIDTH / 2, GAME_HEIGHT / 4);
	dxFont.printC("Press ESC to resume", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 2);
	dxFont.printC("Press B to exit", GAME_WIDTH / 2, (GAME_HEIGHT / 4) * 3);
}

void PauseState::update(float frameTime)
{

}

void PauseState::handleInput(Input* input)
{
	// Testing
	// Unpauses the game
	if (input->wasKeyPressed(ESC_KEY))
		unpausegame();
	// Exits the game (Main menu)
	else if (input->wasKeyPressed(B_KEY))
		exitgame();
}