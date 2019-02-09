#include "GroundedState.h"



GroundedState::GroundedState()
{
}


GroundedState::~GroundedState()
{
}

PlayerState* GroundedState::handleInput(Player& player, Input* input)
{
	if (input->isKeyDown(player.getPK()->getUp()))		// jump from ground
	{
		if (player.actionEnum != STATE_ATTACK && player.actionEnum != STATE_STAGGERED)
		{
			player.getMovementComponent()->setY_Velocity(-PlayerNS::JUMP_VELOCITY*player.speedmultiplier);
			player.jumpcooldown = PlayerNS::JUMP_CD;
			player.canjump = false;
		}
	}
	if (input->isKeyDown(player.getPK()->getDown()))	// duck down
	{
		// duck down
	}

	if (input->isKeyDown(player.getPK()->getLeft()))	// move left
	{
		switch (player.actionEnum)
		{
		case STATE_IDLE:
			player.playerface = -1;
			player.getMovementComponent()->setX_Force(-player.getSpeed() * player.speedmultiplier);
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
			player.getMovementComponent()->setX_Force(player.getSpeed() * player.speedmultiplier);
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

void GroundedState::update(Player & player, float frameTime)
{
	// use forces for friction
	// reduce the players velocity for friction
	if (player.getMovementComponent()->getX_Velocity() !=0)
	{
		//friction formula??
		player.getMovementComponent()->setX_Velocity(player.getMovementComponent()->getX_Velocity()-(player.getMovementComponent()->getX_Velocity()*MovementNS::FRICTION)*frameTime);
		if (player.getMovementComponent()->getX_Velocity() > 0)
		{
			player.getMovementComponent()->setX_Velocity(player.getMovementComponent()->getX_Velocity() - MovementNS::FRICTION_CONST*frameTime);
		}
		else if (player.getMovementComponent()->getX_Velocity() < 0)
		{
			player.getMovementComponent()->setX_Velocity(player.getMovementComponent()->getX_Velocity() + MovementNS::FRICTION_CONST*frameTime);
		}
	}


}

void GroundedState::enter(Player & player)
{
	player.airEnum = STATE_GROUNDED;
	player.airJump = true;

	if (player.actionEnum != STATE_ATTACK)
	{
		player.setAnimationComplete(false);
		player.setFrames(PlayerNS::P1_IDLE_START, PlayerNS::P1_IDLE_END);
		player.setCurrentFrame(PlayerNS::P1_IDLE_START);
		player.setLoop(true);
	}
}

void GroundedState::exit(Player & player)
{
}
