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

	buttonList[0].setSelectedK(true);
	buttonList[0].setCurrentFrame(buttonNS::HOVER_BUTTON);
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
	if (input->isKeyDown(W_KEY))
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i].getSelectedK())
			{
				buttonList[i].setSelectedK(false);
				
				if (i != 0)
				{
					// Moves up the list
					buttonList[i - 1].setSelectedK(true);
					buttonList[i - 1].setCurrentFrame(buttonNS::HOVER_BUTTON);
				}

				else if (i == 0)
				{
					// Needs to loop around the vector
					buttonList[buttonList.size() - 1].setSelectedK(true);
					buttonList[buttonList.size() - 1].setCurrentFrame(buttonNS::HOVER_BUTTON);
				}

				input->keyUp(W_KEY);		// <-- Doesn't register multiple presses
				break;
			}
		}
	}

	if (input->isKeyDown(S_KEY))
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i].getSelectedK())
			{
				buttonList[i].setSelectedK(false);

				if (i != buttonList.size() - 1)
				{
					// Moves down the list
					buttonList[i + 1].setSelectedK(true);
					buttonList[i + 1].setCurrentFrame(buttonNS::HOVER_BUTTON);
				}

				else if (i == buttonList.size() - 1)
				{
					// Needs to loop around the vector
					buttonList[0].setSelectedK(true);
					buttonList[0].setCurrentFrame(buttonNS::HOVER_BUTTON);
				}

				input->keyUp(S_KEY);		// <-- Doesn't register multiple presses
				break;
			}
		}
	}

	if (input->isKeyDown(ENTER_KEY))
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i].getSelectedK())
			{
				// Start
				if (i == 0)
				{
					buttonList[i].setSelectedK(false);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					startGame();
				}

				// Options
				else if (i == 1)
				{
					buttonList[i].setSelectedK(false);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					optionsMenu();
				}

				// Exit
				else if (i == 2)
				{
					buttonList[i].setSelectedK(false);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					game->exitGame();
				}
			}
		}

		input->keyUp(ENTER_KEY);		// <-- Doesn't register multiple presses
	}



	// Mouse
	for (int i = 0; i < buttonList.size(); i++)
	{
		// Resets 'Selected' state
		buttonList[i].setSelectedM(false);

		// Checks to see which button is hovered over
		if (buttonList[i].mouseOver(input))
		{
			// Changes the frame to look as if it's being hovered
			buttonList[i].setSelectedM(true);
			buttonList[i].setCurrentFrame(buttonNS::HOVER_BUTTON);
		}

		else if (!buttonList[i].mouseOver(input) && !buttonList[i].getSelectedK())
		{
			buttonList[i].setSelectedM(false);
			buttonList[i].setCurrentFrame(buttonNS::IDLE_BUTTON);
		}
	}

	if (input->getMouseLButton())
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i].getSelectedM())
			{
				if (i == 0)
				{
					// If i == 0, it means this is the start button
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					startGame();
				}

				else if (i == 1)
				{
					// If i == 1, it means this is the option button
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					input->setMouseLButton(false);		// <-- Doesn't register multiple clicks
					optionsMenu();
				}

				else if (i == 2)
				{
					// If i == 2, it means this is the exit button
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					game->exitGame();
				}
			}
		}
	}
}