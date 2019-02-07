#ifndef _OPTION_STATE_H
#define _OPTION_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "GameState.h"

// Makes it public so that we can derive the functions from this class
class OptionState : public GameState
{
private:

	// Changes the state to "MenuState"
	void exitOption();

public:

	// Constructor
	OptionState(SmashRipoff* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void ai();
	virtual void collisions();
	virtual void handleInput(Input* input);

};

#endif // _OPTION_STATE_H