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
#include "heart.h"
#include "Landmine.h";

//=============================================================================
// This class is the core of the game
//=============================================================================
class SmashRipoff : public Game
{
private:

    // old stuff that should be removed(?)
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
	TextureManager playerTextures;
    Ship    ship1, ship2;           // spaceships
    Planet  planet;					// the planet
    Image   nebula;					// backdrop image
	Player  player;

	// new stuff
	TextureManager projectileTexture;
	TextureManager platformTexture;
	Platform platform;
	Platform platform1;
	Platform platformUpList[NO_PLATFORMS];
	Platform platformDownList[NO_PLATFORMS];
	//bool shootable = true;

	// -Hearts-
	static const int MAX_HEALTH = 3;
	TextureManager heartTexture;
	Image heart;

	// Players' Health
	Heart hunterHealth[MAX_HEALTH];
	Heart priestessHealth[MAX_HEALTH];
	// List starts from 0
	int hunterHP = 2;
	int priestessHP = 2;
	// Players' Knockback

	// Landmine
	Landmine landmine;
	TextureManager landmineTexture;
	bool isPaused;
	int nextIntervalValue = 0;

public:

    // Constructor
    SmashRipoff();

    // Destructor
    ~SmashRipoff();

    // Initialize the game
    void initialize(HWND hwnd);
	void update(Timer *gameTimer);      // must override pure virtual from Game
	void ai(Timer *gameTimer);          // "
	void collisions(Timer *gameTimer);  // 
    void render();      // "

    void releaseAll();
    void resetAll();
	float YVelocity = -TILE_SIZE * 4;
};

#endif // _SMASHRIPOFF_H