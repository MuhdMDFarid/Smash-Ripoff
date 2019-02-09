#include <iostream>
#include "OptionState.h"

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

}

void OptionState::exitOption()
{
	// Transitions from "OptionState" to "MenuState"
	game->popState();
}

void OptionState::draw()
{
	// Draws all the necessary assets
	game->optionBackground.draw();
	game->titleFont.printC("Options", GAME_WIDTH / 2, gameNS::tPoint_Size);

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
					input->setMouseLButton(false);		// <-- Doesn't register multiple clicks
					exitOption();
				}
			}
		}
	}
}