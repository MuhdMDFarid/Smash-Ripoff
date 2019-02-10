//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _AirborneState_H
#define _AirborneState_H
#define WIN32_LEAN_AND_MEAN

#include "PlayerState.h"

class AirborneState : public PlayerState
{
public:
	AirborneState();
	~AirborneState();
	PlayerState* handleInput(Player& player, Input* input /*other input*/);
	void update(Player& player, float frameTime);
	void enter(Player& player);
	void exit(Player& player);
};

#endif