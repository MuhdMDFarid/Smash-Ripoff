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
	//if (player.getAnimationComplete()||player.getCurrentFrame()<player.getStartFrame()/*when moveset is ended*/)
	if(player.skill->isFinished())
	{// if condition should be based on moveset rather than animation i think
		PlayerState* istate = new IdleState();
		if (istate != NULL)
		{
			player.action->exit(player);
			delete player.action;
			player.action = istate;
			player.action->enter(player);
		}
		//player.actionEnum = STATE_IDLE;
		//player.action = new IdleState();
		//player.action->enter(player);
	}
}

void AttackState::enter(Player& player)
{
	player.actionEnum = STATE_ATTACK;

	player.setAnimationComplete(false);
	player.setLoop(false);
	//player.setFrames(PlayerNS::P1_ATTACK_START, PlayerNS::P1_ATTACK_END);
	player.setCurrentFrame(player.getStartFrame());

	/*
	// the actual attack may not be here
	//player.punch(&projecti)
	///////////////
	//player.newhitbox = new Attack_Hitbox();

	//// create hitbox
	//if (!player.newhitbox->initialize(player.game, 32, 32, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	//player.newhitbox->setScale(5);

	//// set hitbox position
	//player.newhitbox->setX(player.getX() + player.getWidth());
	//player.newhitbox->setY(player.getY() + (player.getHeight() - player.newhitbox->getHeight()*player.newhitbox->getScale()) / 2);		//centers the Y coords of hitbox to player


	//player.hitboxlist.push_back(player.newhitbox);
	*/
}

void AttackState::exit(Player& player)
{
	//switch (player.airEnum)
	//{
	//case STATE_GROUNDED:
	//	player.setAnimationComplete(false);
	//	player.setFrames(PlayerNS::P1_IDLE_START, PlayerNS::P1_IDLE_END);
	//	player.setCurrentFrame(PlayerNS::P1_IDLE_START);
	//	player.setLoop(true);

	//case STATE_AIRBORNE:
	//	player.setAnimationComplete(false);
	//	player.setFrames(PlayerNS::P1_AIRBORNE_START, PlayerNS::P1_AIRBORNE_END);
	//	player.setCurrentFrame(PlayerNS::P1_AIRBORNE_START);
	//	player.setLoop(true);		
	//}
}

PlayerState* AttackState::interrupt(Player& player,float stunduration)
{
	// code to cancel all attacks
	//...
	player.skill->cancel();
	return PlayerState::interrupt(player,stunduration);		// temporary interrupt code
}