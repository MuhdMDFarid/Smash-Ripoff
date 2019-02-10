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

	// Variables
	TextureManager menuBackgroundTexture;
	Image menuBackground;
	TextDX menuFont;

public:
	
	// Constructor
	MenuState(Game* game);

	// Destructor
	~MenuState();

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(Timer *gameTimer);
	virtual void handleInput(Input* input);

	virtual void releaseAll();
	virtual void resetAll();
};

#endif // _MENU_STATE_H