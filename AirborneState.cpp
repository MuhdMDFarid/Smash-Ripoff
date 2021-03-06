//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "AirborneState.h"



AirborneState::AirborneState()
{

}

AirborneState::~AirborneState()
{
}

PlayerState* AirborneState::handleInput(Player& player, Input* input)
{
	if (input->isKeyDown(player.getPK()->getUp()))		// air jump
	{
		if (player.canjump && player.actionEnum!= STATE_ATTACK && player.actionEnum != STATE_STAGGERED)
		{
			if (player.airJump)
			{
				player.getMovementComponent()->setY_Velocity(-PlayerNS::JUMP_VELOCITY*player.speedmultiplier);
				player.airJump = false;
				player.jumpcooldown = PlayerNS::JUMP_CD;
				player.canjump = false;
				//jumpcooldown = 2;
			}
		}
	}
	if (input->isKeyDown(player.getPK()->getDown()))	// dive down
	{
		switch (player.actionEnum)
		{
		case STATE_IDLE:
			player.getMovementComponent()->setY_Force(player.getSpeed()*player.speedmultiplier);
		case STATE_ATTACK:
			// down key while attacking if any
			NULL;
		case STATE_STAGGERED:
			// down key while staggered if any
			NULL;
		}
	}
	else
	{
		player.getMovementComponent()->setY_Force(0);
	}

	if (input->isKeyDown(player.getPK()->getLeft()))	// move left
	{
		switch (player.actionEnum)
		{
		case STATE_IDLE:
			player.playerface = -1;
			player.getMovementComponent()->setX_Force(-player.getSpeed() * player.speedmultiplier/2);
		case STATE_ATTACK:
			// down key while attacking if any
			NULL;
		case STATE_STAGGERED:
			// down key while staggered if any
			NULL;
		}
	}
	else if (input->isKeyDown(player.getPK()->getRight()))	// move right
	{
		switch (player.actionEnum)
		{
		case STATE_IDLE:
			player.playerface = 1;
			player.getMovementComponent()->setX_Force(player.getSpeed() * player.speedmultiplier / 2);
		case STATE_ATTACK:
			// down key while attacking if any
			NULL;
		case STATE_STAGGERED:
			// down key while staggered if any
			NULL;
		}
	}
	else { player.getMovementComponent()->setX_Force(0); }
	return NULL;	// return NULL 
}

void AirborneState::update(Player& player, float frameTime)
{
	player.getMovementComponent()->setY_Velocity(player.getMovementComponent()->getY_Velocity() + GRAVITY * frameTime);
}

void AirborneState::enter(Player& player)
{
	player.airEnum = STATE_AIRBORNE;

	if (player.actionEnum == STATE_IDLE)
	{
		player.setAnimationComplete(false);
		player.setFrames(PlayerNS::P1_AIRBORNE_START, PlayerNS::P1_AIRBORNE_END);
		player.setCurrentFrame(PlayerNS::P1_AIRBORNE_START);
		player.setLoop(true);
	}
}

void AirborneState::exit(Player& player)
{
}
