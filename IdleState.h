//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _IdleState_H
#define _IdleState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"

class IdleState : public PlayerState
{
public:
	IdleState();
	~IdleState();
	PlayerState* handleInput(Player& player, Input* input /*other input*/);
	void update(Player& player, float frameTime);
	void enter(Player& player);
	void exit(Player& player);
	PlayerState* interrupt(Player& player,float stunduration);
};

#endif