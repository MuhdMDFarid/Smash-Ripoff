#ifndef _CONTROLLED_PROJECTILE_HITBOX_H
#define _CONTROLLED_PROJECTILE_HITBOX_H
#define WIN32_LEAN_AND_MEAN

#include "Projectile_Hitbox.h"
#include "Player.h"

class IdleState;

namespace CPHNS
{
	const float TURNSPEED = 200;
}

class Controlled_Projectile_Hitbox : public Projectile_Hitbox
{
private:
	float maxVelocity=100;
	float moveAngle = 90;
public:
	Controlled_Projectile_Hitbox();
	Controlled_Projectile_Hitbox(float velocity);
	~Controlled_Projectile_Hitbox();

	virtual void update(float frameTime, Player& player);
	void collided();

	void setMaxV(float mV) { maxVelocity = mV; }
};

#endif