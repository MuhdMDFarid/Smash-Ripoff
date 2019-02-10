//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G


#include "Controlled_Projectile_Hitbox.h"

#include "IdleState.h"

Controlled_Projectile_Hitbox::Controlled_Projectile_Hitbox()
{
}

Controlled_Projectile_Hitbox::Controlled_Projectile_Hitbox(float velocity)
{
	maxVelocity = velocity;
}


Controlled_Projectile_Hitbox::~Controlled_Projectile_Hitbox()
{
}

void Controlled_Projectile_Hitbox::update(float frameTime, Player & player)
{

	//Hitbox::update(frameTime);
	switch (player.actionEnum)
	{
	case STATE_ATTACK:
		if (getActive())
		{
			if (input->isKeyDown(player.getPK()->getUp()))
			{
				if (moveAngle >= 90 && moveAngle <= 270)		// if moving in left direction
				{
					moveAngle -= CPHNS::TURNSPEED*frameTime;		// turn clockwise
				}
				else/*if (moveAngle < 90 || moveAngle > 270)*/		// if moving in right direction
				{
					moveAngle += CPHNS::TURNSPEED*frameTime;		// turn anti-clockwise
				}
			}
			else if (input->isKeyDown(player.getPK()->getDown()))
			{
				if (moveAngle >= 90 && moveAngle <= 270)		// if moving in left direction
				{
					moveAngle += CPHNS::TURNSPEED*frameTime;		// turn anti-clockwise
				}
				else/*if (moveAngle < 90 || moveAngle > 270)*/		// if moving in right direction
				{
					moveAngle -= CPHNS::TURNSPEED*frameTime;		// turn clockwise
				}
			}
			if (input->isKeyDown(player.getPK()->getLeft()))
			{
				if (moveAngle >= 0 && moveAngle <= 180)		// if moving in up direction
				{
					moveAngle += CPHNS::TURNSPEED*frameTime;		// turn anti-clockwise
				}
				else /*if (moveAngle > 180 || moveAngle <= 360)*/		// if moving in down direction
				{
					moveAngle -= CPHNS::TURNSPEED*frameTime;		// turn clockwise
				}
			}
			else if (input->isKeyDown(player.getPK()->getRight()))
			{
				if (moveAngle >= 0 && moveAngle <= 180)		// if moving in up direction
				{
					moveAngle -= CPHNS::TURNSPEED*frameTime;		// turn clockwise
				}
				else/*if (moveAngle > 180 || moveAngle <= 360)*/		// if moving in down direction
				{
					moveAngle += CPHNS::TURNSPEED*frameTime;		// turn anti-clockwise
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

	}

	Projectile_Hitbox::update(frameTime, player);

	if (isExpired())
	{
		PlayerState* istate = new IdleState();
		if (istate != NULL)
		{
			player.action->exit(player);
			delete player.action;
			player.action = istate;
			player.action->enter(player);
		}
	}
}

void Controlled_Projectile_Hitbox::collided()
{
	Projectile_Hitbox::collided();
	//PlayerState* istate = new IdleState();
	//if (istate != NULL)
	//{
	//	player.action->exit(player);
	//	delete player.action;
	//	player.action = istate;
	//	player.action->enter(player);
	//}
}
