//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

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
	// Changes the state to "PlayState"
	void playAgain();

public:

	// Constructor
	HunterDeathState(SmashRipoff* game);

	// ======================
	// Functions (inherited from GameState)
	// ======================
	virtual void draw();
	virtual void update(float frameTime);
	virtual void ai();
	virtual void collisions();
	virtual void handleInput(Input* input);

};

#endif // _HUNTER_DEATH_STATE