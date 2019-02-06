#ifndef _PRIESTESS_DEATH_STATE
#define _PRIESTESS_DEATH_STATE
#define WIN32_LEAN_AND_MEAN

#include "GameState.h"

// Makes it public so that we can derive the functions from this class
class PriestessDeathState : public GameState
{
private:

	// Changes the state to "MenuState"
	void mainMenu();

	// Variables
	TextureManager priestessDeathTexture;
	Image priestessBackground;
	TextDX priestessFont;

public:

	// Constructor
	PriestessDeathState(Game* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void handleInput(Input* input);
};

#endif // _PRIESTESS_DEATH_STATE