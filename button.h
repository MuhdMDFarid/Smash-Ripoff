#ifndef _BUTTON_H
#define _BUTTON_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace buttonNS
{
	const int WIDTH = 32;					// image width
	const int HEIGHT = 32;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;
}

// inherits from Entity class
class Button : public Entity
{
public:

	// Constructor
	Button();

	// ======================
	// Functions
	// ======================
	void mouseHover();
};

#endif // _BUTTON_H