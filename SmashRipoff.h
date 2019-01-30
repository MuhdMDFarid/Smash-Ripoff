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
#include <vector>

//=============================================================================
// This class is the core of the game
//=============================================================================
class SmashRipoff : public Game
{
private:

    // game items
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
	TextureManager playerTextures;
    Ship    ship1, ship2;           // spaceships
    Planet  planet;         // the planet
    Image   nebula;         // backdrop image
	Player  player;

	// new stuff
	TextureManager projectileTexture;
	TextureManager platformTexture;
	Platform platform;
	//bool shootable = true;

public:

    // Constructor
    SmashRipoff();

    // Destructor
    virtual ~SmashRipoff();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif // _SMASHRIPOFF_H