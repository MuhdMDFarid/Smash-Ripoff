#include "Controlled_Projectile_Hitbox.h"



Controlled_Projectile_Hitbox::Controlled_Projectile_Hitbox()
{
}


Controlled_Projectile_Hitbox::~Controlled_Projectile_Hitbox()
{
}

void Controlled_Projectile_Hitbox::update(float frameTime, Player & player)
{

	//Hitbox::update(frameTime);
	if (getActive())
	{
		if (input->isKeyDown(player.getPK()->getUp()))
		{
			if (moveAngle >= 90 && moveAngle <= 270)		// if moving in left direction
			{
				moveAngle -= CPHNS::turnspeed*frameTime;		// turn clockwise
			}
			if (moveAngle < 90 || moveAngle > 270)		// if moving in right direction
			{ 
				moveAngle += CPHNS::turnspeed*frameTime;		// turn anti-clockwise
			}
		}
		else if (input->isKeyDown(player.getPK()->getDown()))
		{
			if (moveAngle >= 90 && moveAngle <= 270)		// if moving in left direction
			{
				moveAngle += CPHNS::turnspeed*frameTime;		// turn anti-clockwise
			}
			if (moveAngle < 90 || moveAngle > 270)		// if moving in right direction
			{
				moveAngle -= CPHNS::turnspeed*frameTime;		// turn clockwise
			}
		}
		if (input->isKeyDown(player.getPK()->getLeft()))
		{
			if (moveAngle >= 0 && moveAngle < 180)		// if moving in up direction
			{
				moveAngle += CPHNS::turnspeed*frameTime;		// turn anti-clockwise
			}
			if (moveAngle >= 180 || moveAngle < 360)		// if moving in down direction
			{
				moveAngle -= CPHNS::turnspeed*frameTime;		// turn clockwise
			}
		}
		else if (input->isKeyDown(player.getPK()->getRight()))
		{
			if (moveAngle >= 0 && moveAngle < 180)		// if moving in up direction
			{
				moveAngle *= CPHNS::turnspeed*frameTime;		// turn clockwise
			}
			if (moveAngle >= 180 || moveAngle < 360)		// if moving in down direction
			{
				moveAngle += CPHNS::turnspeed*frameTime;		// turn anti-clockwise
			}
		}

		// loops the angle back
		if (moveAngle > 360) { moveAngle -= 360; }
		if (moveAngle < 0) { moveAngle += 360; }

		//moveAngle = 0;
		setVelocity(
			maxVelocity * cos(moveAngle * PI / 180),		// x vel
			maxVelocity * -sin(moveAngle  * PI / 180)		// y vel
		);
	}
	Projectile_Hitbox::update(frameTime, player);

}
