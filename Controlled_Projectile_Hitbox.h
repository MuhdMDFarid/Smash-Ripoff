#ifndef _CONTROLLED_PROJECTILE_HITBOX_H
#define _CONTROLLED_PROJECTILE_HITBOX_H
#define WIN32_LEAN_AND_MEAN

#include "Projectile_Hitbox.h"
#include "Player.h"

namespace CPHNS
{
	const float turnspeed = 500;
}

class Controlled_Projectile_Hitbox : public Projectile_Hitbox
{
private:
	float maxVelocity=100;
	float moveAngle = 0;
public:
	Controlled_Projectile_Hitbox();
	~Controlled_Projectile_Hitbox();

	virtual void update(float frameTime, Player& player);
};

#endif