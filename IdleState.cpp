//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "IdleState.h"

#include "AttackState.h"

IdleState::IdleState()
{
}


IdleState::~IdleState()
{
}

PlayerState* IdleState::handleInput(Player& player, Input* input)
{
	if (input->isKeyDown(player.getPK()->getNormal()))			// input should be based on key bindings
	{// normal
		switch (player.airEnum)
		{
		case STATE_GROUNDED:
			// execute player ground normal based on moveset and key combo
			player.setFrames(PlayerNS::P1_ATTACK_START,PlayerNS::P1_ATTACK_END);		//settting frames should be based on moveset
			player.normalS();
		case STATE_AIRBORNE:
			// execute player aerial normal based on moveset and key combo
			player.setFrames(PlayerNS::P1_ATTACK_START, PlayerNS::P1_ATTACK_END);		//settting frames should be based on moveset
			player.normalS();
		}
		return new AttackState();
	}
	else if(input->isKeyDown(player.getPK()->getSpecial()))		// input should be based on key bindings
	{// special
		switch (player.airEnum)
		{
		case STATE_GROUNDED:
			// execute player ground special based on moveset and key combo
			player.setFrames(PlayerNS::P1_SLAM_START, PlayerNS::P1_SLAM_END);			//settting frames should be based on moveset
			player.specialS();

		case STATE_AIRBORNE:
			// execute player aerial special based on moveset and key combo
			player.setFrames(PlayerNS::P1_SLAM_START, PlayerNS::P1_SLAM_END);		//settting frames should be based on moveset
			player.specialS();

		}
		return new AttackState();
	}
	
	return NULL;	// return NULL

}

void IdleState::update(Player& player, float frameTime)
{
	//stuff
}

void IdleState::enter(Player& player)
{
	player.actionEnum = STATE_IDLE;
	//switch (player.airEnum)
	//{
	//case STATE_AIRBORNE:
	//	player.setAnimationComplete(false);
	//	player.setFrames(PlayerNS::P1_AIRBORNE_START, PlayerNS::P1_AIRBORNE_END);
	//	player.setCurrentFrame(PlayerNS::P1_AIRBORNE_START);
	//	player.setLoop(true);
	//case STATE_GROUNDED:
	//	player.setAnimationComplete(false);
	//	player.setFrames(PlayerNS::P1_IDLE_START, PlayerNS::P1_IDLE_END);
	//	player.setCurrentFrame(PlayerNS::P1_IDLE_START);
	//	player.setLoop(true);
	//}
	if (player.airEnum == STATE_AIRBORNE)
	{
		player.setAnimationComplete(false);
		player.setFrames(PlayerNS::P1_AIRBORNE_START, PlayerNS::P1_AIRBORNE_END);
		player.setCurrentFrame(PlayerNS::P1_AIRBORNE_START);
		player.setLoop(true);
	}
	else if (player.airEnum == STATE_GROUNDED)
	{
		player.setAnimationComplete(false);
		player.setFrames(PlayerNS::P1_IDLE_START, PlayerNS::P1_IDLE_END);
		player.setCurrentFrame(PlayerNS::P1_IDLE_START);
		player.setLoop(true);
	}
}

void IdleState::exit(Player& player)
{
	player.setX_Force(0);
	player.setY_Force(0);
}

PlayerState* IdleState::interrupt(Player& player, float stunduration)
{
	return PlayerState::interrupt(player,stunduration);		// temporary interrupt code
}