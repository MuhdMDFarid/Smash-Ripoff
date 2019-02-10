//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "Damage_Component.h"



Damage_Component::Damage_Component()
{
	damage = 1;			// damage given to player
	angle = 45;			// angle player is thrown at in degrees
	force = 0;			// force of knockback
}


Damage_Component::~Damage_Component()
{
}

D3DXVECTOR2 Damage_Component::calculateVector()
{
	//angle *PI/180=1
	int rawXforce = force * (cos(angle*PI/180));
	int rawYforce = force * -(sin(angle*PI/180));
	return D3DXVECTOR2(rawXforce, rawYforce);
}

void Damage_Component::receive(int message)
{
}

void Damage_Component::execute()
{
}
