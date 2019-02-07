#include "button.h"

//=============================================================================
// Default Constructor
//=============================================================================
Button::Button() : Entity()
{
	spriteData.width = buttonNS::WIDTH;           // size of asteroid
	spriteData.height = buttonNS::HEIGHT;
	spriteData.x = buttonNS::X;                   // location on screen
	spriteData.y = buttonNS::Y;
	spriteData.rect.bottom = buttonNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = buttonNS::WIDTH;
}