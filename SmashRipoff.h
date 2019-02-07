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
#include "HealthPotion.h"
#include "heart.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class SmashRipoff : public Game
{
private:

    // old stuff that should be removed(?)
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTexture;    // game texture
	TextureManager playerTexture;
    //Ship    ship1, ship2;           // spaceships
    Planet  planet;					// the planet
    Image   nebula;					// backdrop image
	Player  player;

	// new stuff
	TextureManager projectileTexture;
	TextureManager platformTexture;
	//Platform platform;
	Platform platform1;
	Platform platformUpList[NO_PLATFORMS];
	Platform platformDownList[NO_PLATFORMS];
	TextureManager speedpotionTexture;
	TextureManager healthpotionTexture;
	SpeedPotion speedpotion;
	HealthPotion healthpotion;
	//bool shootable = true;

	// -Hearts-
	TextureManager heartTexture;
	Image heart;

	
	// Players' Knockback

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
};

#endif // _SMASHRIPOFF_H