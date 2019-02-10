//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "PlayerState.h"
#include "StaggeredState.h"


PlayerState::PlayerState()
{
}


PlayerState::~PlayerState()
{
}

PlayerState* PlayerState::interrupt(Player & player,float stunduration)
{
	return new StaggeredState(stunduration);


	//player.getMovementComponent()->setY_Velocity(player.getMovementComponent()->getY_Velocity() - 100);
	//PlayerState* astate = action->i
	//player.action->exit(player);
	//delete player.action;
	//action = astate;
	//action->enter(*this);
}
