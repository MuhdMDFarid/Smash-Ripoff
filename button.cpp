#include "button.h"

//=============================================================================
// Default Constructor
//=============================================================================
Button::Button()
{
	selectedMouse = false;
	selectedKey = false;
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