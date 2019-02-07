#include "PlayerState.h"
#include "StaggeredState.h"


PlayerState::PlayerState()
{
}


PlayerState::~PlayerState()
{
}

PlayerState* PlayerState::interrupt(Player & player,float stunduration)
{
	return new StaggeredState(stunduration);


	//player.getMovementComponent()->setY_Velocity(player.getMovementComponent()->getY_Velocity() - 100);
	//PlayerState* astate = action->i
	//player.action->exit(player);
	//delete player.action;
	//action = astate;
	//action->enter(*this);
}
