#include "AttackState.h"

#include "IdleState.h"


AttackState::AttackState()
{
}


AttackState::~AttackState()
{
}

PlayerState* AttackState::handleInput(Player& player, Input* input)
{
	return NULL;	// temporarily return NULL state. change later

}

void AttackState::update(Player& player, float frameTime)
{
	//stuff

	// when Attack is Completed SHOULDN'T BE BASED ON ANIMATION
	// Some animation shouldn't be cancelled like attack animations
	if (/*player.getAnimationComplete()*/player.getCurrentFrame()==player.getEndFrame())
	{
		exit(player);
		player.action = new IdleState();
		player.action->enter(player);
		//player.actionEnum = STATE_IDLE;
		//player.action = new IdleState();
		//player.action->enter(player);
	}
}

void AttackState::enter(Player& player)
{
	player.actionEnum = STATE_ATTACK;

	player.setAnimationComplete(false);
	player.setFrames(PlayerNS::P1_ATTACK_START, PlayerNS::P1_ATTACK_END);
	player.setCurrentFrame(PlayerNS::P1_ATTACK_START);
	player.setLoop(false);

	// the actual attack may not be here
	//player.punch(&projecti)
}

void AttackState::exit(Player& player)
{
	
}