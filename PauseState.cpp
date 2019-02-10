#include <iostream>
#include "PauseState.h"
#include "MenuState.h"
#include "game.h"

PauseState::PauseState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Empties the vector
	buttonList.clear();

	// --Buttons--
	// Resume
	game->resumeButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->resumeButton.setY((GAME_HEIGHT / 5) * 3);
	buttonList.push_back(game->resumeButton);

	// Exit
	game->exitButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->exitButton.setY((GAME_HEIGHT / 5) * 4);
	buttonList.push_back(game->exitButton);
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
	game->resetGame();
	game->pushState(new MenuState(game));
}

void PauseState::draw()
{
	// Draws all the necessary assets
	game->pauseBackground.draw();
	game->titleFont.printC("PAUSED", GAME_WIDTH / 2, gameNS::tPoint_Size);

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].draw();
	}

	game->buttonFont.printC("Resume", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 3);
	game->buttonFont.printC("Exit", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 4);
}

void PauseState::update(float frameTime)
{

}

void PauseState::ai()
{

}

void PauseState::collisions()
{

}

void PauseState::handleInput(Input* input)
{
	// Keyboard
	// Unpauses the game
	if (input->isKeyDown(ESC_KEY))
	{
		input->keyUp(ESC_KEY);
		unpauseGame();
	}

	if (input->isKeyDown(VK_UP))
	{
		//
	}

	if (input->isKeyDown(VK_DOWN))
	{
		//
	}


	// Mouse
	for (int i = 0; i < buttonList.size(); i++)
	{
		// Checks to see which button is hovered over
		if (buttonList[i].mouseOver(input))
		{
			// Changes the frame to look as if it's being hovered
			buttonList[i].setSelected(true);
			buttonList[i].setCurrentFrame(buttonNS::HOVER_BUTTON);
		}

		else if (!buttonList[i].mouseOver(input))
		{
			buttonList[i].setSelected(false);
			buttonList[i].setCurrentFrame(buttonNS::IDLE_BUTTON);
		}
	}

	if (input->getMouseLButton())
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i].getSelected())
			{
				if (i == 0)
				{
					// If i == 0, it means this is the start button
					buttonList[i].setClicked(true);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					unpauseGame();
				}

				else if (i == 1)
				{
					// If i == 1, it means this is the option button
					buttonList[i].setClicked(true);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					input->setMouseLButton(false);		// <-- Doesn't register multiple clicks
					exitGame();
				}
			}
		}
	}
}