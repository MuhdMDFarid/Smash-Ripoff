#ifndef _SMASHRIPOFF_H             // Prevent multiple definitions if this 
#define _SMASHRIPOFF_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "ship.h"
#include "Player.h"
#include "Projectile.h"
#include "Platform.h"
#include "SpeedPotion.h"
#include "heart.h"
#include <vector>

//=============================================================================
// This class is the core of the game
//=============================================================================
class GameState;
class button;

class SmashRipoff : public Game
{
private:

	// States - Texture - Play
	TextureManager nebulaTexture;
	TextureManager gameTexture;
	TextureManager playerTexture;
	TextureManager projectileTexture;
	TextureManager platformTexture;
	TextureManager potionTexture;
	TextureManager heartTexture;

	// States
	// A vector to store game states
	std::vector<GameState*> states;
	// States - Texture
	// States - Texture - Menu
	TextureManager menuBackgroundTexture;
	// States - Texture - Pause
	TextureManager pauseBackgroundTexture;
	// States - Texture - Option
	TextureManager optionBackgroundTexture;
	// States - Texture - Hunter
	TextureManager hunterDeathTexture;
	// States - Texture - Priestess
	TextureManager priestessDeathTexture;

	// Buttons
	std::vector<button*> buttons;

public:

    // Constructor
    SmashRipoff();

    // Destructor
    ~SmashRipoff();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	float YVelocity = -TILE_SIZE * 4;

	// --Buttons--


	// --States--
	// Functions for game states
	void pushState(GameState* state);
	void popState();
	void deleteState();

	// Gets the current state
	GameState* getCurrentState();

	// Font
	TextDX titleFont;
	TextDX buttonFont;

	// States - Image
	// States - Image - Menu
	Image menuBackground;
	// States - Image - Play
	Image   nebula;
	Player  player;
	Planet planet;
	Platform platform1;
	Platform platformUpList[NO_PLATFORMS];
	Platform platformDownList[NO_PLATFORMS];
	Image heart;
	SpeedPotion potion;
	// Players' Health
	Heart hunterHealth[MAX_HEALTH];
	Heart priestessHealth[MAX_HEALTH];
	// List starts from 0
	int hunterHP = 2;
	int priestessHP = 2;
	bool hunterDeath = false;
	bool priestessDeath = false;
	// States - Image - Pause
	Image pauseBackground;
	// States - Image - Option
	Image optionBackground;
	// States - Image - Hunter
	Image hunterBackground;
	// States - Image - Priestess
	Image priestessBackground;
};

#endif // _SMASHRIPOFF_H