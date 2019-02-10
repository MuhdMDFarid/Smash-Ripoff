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

	// Variables
	TextureManager optionBackgroundTexture;
	Image optionBackground;
	TextDX optionFont;

public:

	// Constructor
	OptionState(Game* game);

	// Destructor
	~OptionState();

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(Timer *gameTimer);
	virtual void handleInput(Input* input);

	virtual void releaseAll();
	virtual void resetAll();
};

#endif // _OPTION_STATE_H