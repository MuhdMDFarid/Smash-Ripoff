#ifndef _PLAYERINPUT_COMPONENT_H               // Prevent multiple definitions if this 
#define _PLAYERINPUT_COMPONENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Component.h"

typedef unsigned char UCHAR;

class PlayerInput_Component : public Component
{
	UCHAR upKey = 0;
	UCHAR downKey = 0;
	UCHAR leftKey = 0;
	UCHAR rightKey = 0;
	UCHAR normalKey = 0;
	UCHAR specialKey = 0;

public:
	PlayerInput_Component();
	~PlayerInput_Component();

	// key binding functions
	void bindUp(UCHAR upkey) { upKey = upkey; }
	void bindDown(UCHAR downkey) { downKey = downkey; }
	void bindLeft(UCHAR leftkey) { leftKey = leftkey; }
	void bindRight(UCHAR rightkey) { rightKey = rightkey; }
	void bindNormal(UCHAR normalkey) { normalKey = normalkey; }
	void bindSpecial(UCHAR specialkey) { specialKey = specialkey; }

	UCHAR getUp() { return upKey; }
	UCHAR getDown() { return downKey; }
	UCHAR getLeft() { return leftKey; }
	UCHAR getRight() { return rightKey; }
	UCHAR getNormal() { return normalKey; }
	UCHAR getSpecial() { return specialKey; }

	virtual void receive(int message);
	virtual void execute();
};

#endif