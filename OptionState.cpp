#include <iostream>
#include "OptionState.h"
#include "MenuState.h"

OptionState::OptionState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;

	// Empties the vector
	buttonList.clear();

	// --Buttons--
	// Exit
	game->exitButton.setX((GAME_WIDTH - buttonNS::WIDTH) / 2);
	game->exitButton.setY((GAME_HEIGHT / 5) * 4);
	buttonList.push_back(game->exitButton);

	buttonList[0].setSelectedK(true);
	buttonList[0].setCurrentFrame(buttonNS::HOVER_BUTTON);
}

void OptionState::exitOption()
{
	// Transitions from "OptionState" to "MenuState"
	game->deleteState();
	game->pushState(new MenuState(game));
}

void OptionState::draw()
{
	// Draws all the necessary assets
	game->optionBackground.draw();
	game->titleFont.printC("Option", GAME_WIDTH / 2, gameNS::tPoint_Size);

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].draw();
	}

	game->buttonFont.printC("Exit", GAME_WIDTH / 2, (GAME_HEIGHT / 5) * 4);
}

void OptionState::update(float frameTime)
{

}

void OptionState::ai()
{

}

void OptionState::collisions()
{

}

void OptionState::handleInput(Input* input)
{
	// Keyboard
	if (input->isKeyDown(ENTER_KEY))
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i].getSelectedK())
			{
				// Exit
				if (i == 0)
				{
					buttonList[i].setSelectedK(false);
					buttonList[i].setCurrentFrame(buttonNS::CLICK_BUTTON);
					exitOption();
				}
			}

			input->keyUp(ENTER_KEY);		// <-- Doesn't register multiple presses
		}
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
					input->setMouseLButton(false);		// <-- Doesn't register multiple clicks
					exitOption();
				}
			}
		}
	}
}