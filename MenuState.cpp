#include <iostream>
#include "MenuState.h"
#include "PlayState.h"
#include "OptionState.h"

MenuState::MenuState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Empties the vector
	buttonList.clear();

	// --Buttons--
	// Start
	game->startButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->startButton.setY((GAME_HEIGHT / 5) * 2);
	buttonList.push_back(game->startButton);

	// Option
	game->optionButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->optionButton.setY((GAME_HEIGHT / 5) * 3);
	buttonList.push_back(game->optionButton);

	// Exit
	game->exitButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->exitButton.setY((GAME_HEIGHT / 5) * 4);
	buttonList.push_back(game->exitButton);
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
	game->menuBackground.draw();
	game->titleFont.printC("Main Menu", GAME_WIDTH / 2, gameNS::tPoint_Size);

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].draw();
	}

	game->buttonFont.printC("Start", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 2);
	game->buttonFont.printC("Options", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 3);
	game->buttonFont.printC("Exit", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 4);
}

void MenuState::update(float frameTime)
{

}

void MenuState::ai()
{

}

void MenuState::collisions()
{

}

void MenuState::handleInput(Input* input)
{
	// Keyboard
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
					startGame();
				}

				else if (i == 1)
				{
					// If i == 1, it means this is the option button
					buttonList[i].setClicked(true);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					input->setMouseLButton(false);		// <-- Doesn't register multiple clicks
					optionsMenu();
				}

				else if (i == 2)
				{
					// If i == 2, it means this is the exit button
					buttonList[i].setClicked(true);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					game->exitGame();
				}
			}
		}
	}
}