#include "AirborneState.h"



AirborneState::AirborneState()
{

}

AirborneState::~AirborneState()
{
}

PlayerState* AirborneState::handleInput(Player& player, Input* input)
{
	if (input->isKeyDown(VK_UP)||input->isKeyDown(W_KEY))
	{
		if (player.canjump && player.actionEnum!= STATE_ATTACK && player.actionEnum != STATE_STAGGERED)
		{
			if (player.airJump)
			{
				player.getMovementComponent()->setY_Velocity(-PlayerNS::JUMP_VELOCITY);
				player.airJump = false;
				player.jumpcooldown = PlayerNS::JUMP_CD;
				player.canjump = false;
				//jumpcooldown = 2;
			}
		}
	}
	return NULL;	// return NULL 
}

void AirborneState::update(Player& player, float frameTime)
{
	player.getMovementComponent()->setY_Velocity(player.getMovementComponent()->getY_Velocity() + GRAVITY * frameTime);
}

void AirborneState::enter(Player& player)
{
	player.airEnum = STATE_AIRBORNE;

	if (player.airEnum != STATE_ATTACK)
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