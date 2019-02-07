#ifndef _HUNTER_DEATH_STATE
#define _HUNTER_DEATH_STATE
#define WIN32_LEAN_AND_MEAN

#include "GameState.h"

// Makes it public so that we can derive the functions from this class
class HunterDeathState : public GameState
{
private:

	// Changes the state to "MenuState"
	void mainMenu();

	// Variables
	TextureManager hunterDeathTexture;
	Image hunterBackground;
	TextDX hunterFont;

public:

	// Constructor
	HunterDeathState(Game* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void handleInput(Input* input);
};

#endif // _HUNTER_DEATH_STATE