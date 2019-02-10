#include <iostream>
#include "HunterDeathState.h"
#include "MenuState.h"

HunterDeathState::HunterDeathState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Empties the vector
	buttonList.clear();

	// --Buttons--
	// Reset (Resume)
	game->resumeButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->resumeButton.setY((GAME_HEIGHT / 5) * 3);
	buttonList.push_back(game->resumeButton);

	// Exit
	game->exitButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->exitButton.setY((GAME_HEIGHT / 5) * 4);
	buttonList.push_back(game->exitButton);

	buttonList[0].setSelectedK(true);
	buttonList[0].setCurrentFrame(buttonNS::HOVER_BUTTON);
}

void HunterDeathState::mainMenu()
{
	// Pops everything from the list and creates a new "MenuState"
	game->deleteState();
	game->resetGame();
	game->pushState(new MenuState(game));
}

void HunterDeathState::playAgain()
{
	// Pops up the "DeathState" (PlayState --> DeathState(popped))
	game->resetGame();
	game->popState();
}

void HunterDeathState::draw()
{
	// Draws all the necessary assets
	game->hunterBackground.draw();
	game->titleFont.printC("Priestess Wins!!", GAME_WIDTH / 2, gameNS::tPoint_Size);

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].draw();
	}

	game->buttonFont.printC("Restart", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 3);
	game->buttonFont.printC("Exit", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 4);
}

void HunterDeathState::update(float frameTime)
{

}

void HunterDeathState::ai()
{

}

void HunterDeathState::collisions()
{

}

void HunterDeathState::handleInput(Input* input)
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
				// Restart
				if (i == 0)
				{
					buttonList[i].setSelectedK(false);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					playAgain();
				}

				// Exit
				else if (i == 1)
				{
					buttonList[i].setSelectedK(false);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					mainMenu();
				}
			}
		}

		input->keyUp(ENTER_KEY);		// <-- Doesn't register multiple presses
	}



	// Mouse
	for (int i = 0; i < buttonList.size(); i++)
	{
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
					playAgain();
				}

				else if (i == 1)
				{
					// If i == 1, it means this is the option button
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					input->setMouseLButton(false);		// <-- Doesn't register multiple clicks
					mainMenu();
				}
			}
		}
	}
}