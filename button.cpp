//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "button.h"

//=============================================================================
// Default Constructor
//=============================================================================
Button::Button() : Entity()
{
	spriteData.width	= buttonNS::WIDTH;			// Size of the button
	spriteData.height	= buttonNS::HEIGHT;
	spriteData.x		= buttonNS::X;				// Location of the button
	spriteData.y		= buttonNS::Y;
	spriteData.rect.bottom = buttonNS::HEIGHT;		// Rectangle to select parts of an image
	spriteData.rect.right = buttonNS::WIDTH;
	setCurrentFrame(currentFrame);
}

bool Button::mouseOver(Input* input)
{
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	if ((mouseX >= spriteData.x && mouseX <= spriteData.x + spriteData.width) &&
		mouseY >= spriteData.y && mouseY <= spriteData.y + spriteData.height)
	{
		return true;
	}

	return false;
}