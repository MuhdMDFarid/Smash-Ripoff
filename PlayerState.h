//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef  _PlayerState_H
#define _PlayerState_H
#define WIN32_LEAN_AND_MEAN

#include "Player.h"
#include "constants.h"


class PlayerState
{
private:

	//Player* player;

public:
	PlayerState();
	~PlayerState();
	virtual PlayerState* handleInput(Player& player, Input* input /*other input*/) = 0;
	virtual void update(Player& player, float frameTime) = 0;
	virtual void enter(Player& player) = 0;
	virtual void exit(Player& player) = 0;
	virtual	PlayerState* interrupt(Player& player,float stunduration);
};

#endif