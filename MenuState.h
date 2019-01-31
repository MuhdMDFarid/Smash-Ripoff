#ifndef _MENU_STATE_H
#define _MENU_STATE_H
#define WIN32_LEAN_AND_MEAN
#include "GameState.h"

// Makes it public so that we can derive the functions from this class
class MenuState : public GameState
{
private:

	// Changes the state to "PlayState"
	void startgame();

public:
	
	// Constructor
	MenuState(Game* game);    

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw(float frameTime);
	virtual void update(float frameTime);
	virtual void handleInput(Input* input);
};

#endif // _MENU_STATE_H