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
	PlayState(Game* game);

	// Destructor
	~PlayState();

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void handleInput(Input* input);

	virtual void releaseAll();
	virtual void resetAll();
};

#endif // _PLAY_STATE_H