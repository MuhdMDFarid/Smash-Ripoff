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
