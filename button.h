#ifndef _BUTTON_H
#define _BUTTON_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>

namespace buttonNS
{
	const int WIDTH = 192;					// image width
	const int HEIGHT = 51;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;						// "
	const int TEXTURE_COLS = 3;				// amount of columns
	
	// --Frames--
	const int currentFrame = 0;				// starts off as idle
	const int IDLE_BUTTON = 0;
	const int HOVER_BUTTON = 1;
	const int CLICK_BUTTON = 2;
}

// inherits from Entity class
class Button : public Entity
{
private:

	// Checks to see if the button is selected (hovered)
	bool selected;
	// Checks to see if the button is clicked
	bool clicked;

public:

	// Constructor(s)
	Button();

	// ======================
	// Functions
	// ======================
	bool getSelected() { return selected; }
	void setSelected(bool b)
	{
		selected = b;
	}

	bool getClicked() { return clicked; }
	void setClicked(bool b)
	{
		clicked = b;
	}

	bool mouseOver(Input* input);
};

#endif // _BUTTON_H