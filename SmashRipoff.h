//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _SMASHRIPOFF_H             // Prevent multiple definitions if this 
#define _SMASHRIPOFF_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
//#include "ship.h"
#include "Player.h"
#include "Projectile_Hitbox.h"
#include "Platform.h"
#include "RotatingPlatform.h"
#include "Landmine.h"
#include "meteor.h"
#include "SpeedPotion.h"
#include "HealthPotion.h"
#include "heart.h"
#include "button.h"
#include "Skill.h"
#include "PlayerInput_Component.h"
//#include <vector>

//=============================================================================
// This class is the core of the game
//=============================================================================
class GameState;

class SmashRipoff : public Game
{
private:

	// States - Texture - Play
	TextureManager nebulaTexture;
	TextureManager gameTexture;
	TextureManager hunterTexture;
	TextureManager priestessTexture;

	//Planet  planet;					// the planet
	//Image   nebula;					// backdrop image
	//Player  player;

	// new stuff
	TextureManager projectileTexture;
	TextureManager platformTexture;
	//Platform platform;
	TextureManager speedpotionTexture;
	TextureManager healthpotionTexture;
	
	//landmine
	TextureManager landmineTexture;
	//bool shootable = true;

	// meteor
	TextureManager meteorTexture;

	// --Hearts--
	//static const int MAX_HEALTH = 3;
	TextureManager heartTexture;
	//Image heart;

	// --States--
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

	// --Button--
	TextureManager buttonTexture;

	// Players' Health
	//Heart hunterHealth[MAX_HEALTH];
	//Heart priestessHealth[MAX_HEALTH];
	// List starts from 0
	//int hunterHP = 2;
	//int priestessHP = 2;
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

	void resetPlayersPosition();

	// --States--
	// Functions for game states
	void pushState(GameState* state);
	void popState();
	void deleteState();

	// Gets the current state
	GameState* getCurrentState();

	// Reset the game
	void resetGame();

	// Font
	TextDX titleFont;
	TextDX buttonFont;

	// Button
	// Button button;
	Button startButton;
	Button optionButton;
	Button resumeButton;
	Button exitButton;

	// States - Image
	// States - Image - Menu
	Image menuBackground;

	// States - Image - Play
	Image   nebula;
	Player  hunter;
	Player priestess;

	SpeedPotion speedpotion;
	HealthPotion healthpotion;

	Planet planet;
	RotatingPlatform platform;
	Platform platform1;
	Platform platformUpList[NO_PLATFORMS];
	Platform platformDownList[NO_PLATFORMS];
	Landmine landmine;
	Meteor meteor;
	Image heart;
	// Players' Health
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