#ifndef _PAUSE_STATE_H
#define _PAUSE_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "GameState.h"

// Makes it public so that we can derive the functions from this class
class PauseState : public GameState
{
private:

	// Changes the state to "PlayState"
	void unpausegame();
	// Changes the state to "MenuState"
	void exitgame();

public:

	// Constructor
	PauseState(Game* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw(float frameTime);
	virtual void update(float frameTime);
	virtual void handleInput(Input* input);

};

#endif // _PAUSE_STATE_H