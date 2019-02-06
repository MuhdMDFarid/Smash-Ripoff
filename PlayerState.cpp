#include "PlayerState.h"



PlayerState::PlayerState()
{
}


PlayerState::~PlayerState()
{
}

void PlayerState::interrupt(Player & player)
{
	player.getMovementComponent()->setY_Velocity(player.getMovementComponent()->getY_Velocity() - 100);
}
