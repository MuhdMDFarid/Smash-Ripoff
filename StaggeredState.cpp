#include "StaggeredState.h"



StaggeredState::StaggeredState()
{
	duration = 0;
}

StaggeredState::StaggeredState(float stunduration)
{
	duration = stunduration;
}


StaggeredState::~StaggeredState()
{
}

PlayerState * StaggeredState::handleInput(Player & player, Input * input)
{
	return NULL;
}

void StaggeredState::update(Player & player, float frameTime)
{
	duration -= frameTime;
	if (duration <= 0)
	{
		recover(player);
	}
}

void StaggeredState::enter(Player & player)
{
	player.actionEnum = STATE_STAGGERED;
	player.getMovementComponent()->setX_Force(0);
	player.getMovementComponent()->setY_Force(0);
	player.setAnimationComplete(false);
	player.setFrames(PlayerNS::P1_STAGGERED_START, PlayerNS::P1_STAGGERED_END);
	player.setCurrentFrame(PlayerNS::P1_STAGGERED_START);
	player.setLoop(true);

}

void StaggeredState::exit(Player & player)
{
	player.canjump = true;
	player.airJump = true;
}

PlayerState * StaggeredState::interrupt(Player & player,float stunduration)
{
	return PlayerState::interrupt(player,stunduration);		// temporary interrupt code
}

void StaggeredState::recover(Player& player)
{
	PlayerState* ststate = new IdleState();
	if (ststate != NULL)
	{
		player.action->exit(player);
		delete player.action;
		player.action = ststate;
		player.action->enter(player);
	}
}
