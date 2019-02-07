#include "heart.h"

//=============================================================================
// Default Constructor
//=============================================================================
Heart::Heart() : Entity()
{
	spriteData.width = heartNS::WIDTH;           // size of asteroid
	spriteData.height = heartNS::HEIGHT;
	spriteData.x = heartNS::X;                   // location on screen
	spriteData.y = heartNS::Y;
	spriteData.rect.bottom = heartNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = heartNS::WIDTH;
}