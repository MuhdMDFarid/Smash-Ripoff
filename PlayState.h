#ifndef _PLAY_STATE_H
#define _PLAY_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "GameState.h"

// Makes it public so that we can derive the functions from this class
class PlayState : public GameState
{
private:

	// Changes the state to "PauseState"
	void pauseGame();

public:

	// Constructor
	PlayState(SmashRipoff* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void ai();
	virtual void collisions();
	virtual void handleInput(Input* input);

};

#endif // _PLAY_STATE_H