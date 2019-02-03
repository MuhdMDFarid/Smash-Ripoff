#include "GroundedState.h"



GroundedState::GroundedState()
{
}


GroundedState::~GroundedState()
{
}

PlayerState* GroundedState::handleInput(Player& player, Input* input)
{
	if (input->isKeyDown(VK_UP) || input->isKeyDown(W_KEY))		// input should be based on key bindings
	{
		if (player.actionEnum != STATE_ATTACK && player.actionEnum != STATE_STAGGERED)
		{
			player.getMovementComponent()->setY_Velocity(-PlayerNS::JUMP_VELOCITY);
			player.jumpcooldown = PlayerNS::JUMP_CD;
			player.canjump = false;
		}
	}
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
