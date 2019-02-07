#ifndef _MENU_STATE_H
#define _MENU_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "GameState.h"


// Makes it public so that we can derive the functions from this class
class MenuState : public GameState
{
private:

	// Changes the state to "PlayState"
	void startGame();
	// Changes the state to "OptionState"
	void optionsMenu();

public:
	
	// Constructor
	MenuState(SmashRipoff* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void ai();
	virtual void collisions();
	virtual void handleInput(Input* input);
};

#endif // _MENU_STATE_H