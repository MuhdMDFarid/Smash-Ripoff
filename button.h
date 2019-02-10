//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _BUTTON_H
#define _BUTTON_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace buttonNS
{
	const int WIDTH = 192;					// image width
	const int HEIGHT = 51;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;						// "
	const int TEXTURE_COLS = 3;				// amount of columns
	
	// --Frames--
	const int currentFrame = 0;					// starts off as idle
	const int IDLE_BUTTON = 0;
	const int HOVER_BUTTON = 1;
	const int CLICK_BUTTON = 2;
}

// inherits from Entity class
class Button : public Entity
{
private:

	// Checks to see if the button is selected (hovered)
	bool selectedMouse = false;
	// Checks to see if the button is selected (keyboard)
	bool selectedKey = false;

public:

	// Constructor(s)
	Button();

	// ======================
	// Functions
	// ======================
	bool getSelectedM() { return selectedMouse; }
	void setSelectedM(bool b)
	{
		selectedMouse = b;
	}

	bool getSelectedK() { return selectedKey; }
	void setSelectedK(bool b)
	{
		selectedKey = b;
	}

	bool mouseOver(Input* input);
};

#endif // _BUTTON_H