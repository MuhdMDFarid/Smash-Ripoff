//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "PK_Thunder.h"

#include "Hitbox.h"
//#include "Projectile_Hitbox.h"
//#include "ActiveState.h"
//#include "CompletedState.h"
//#include "InactiveState.h"

PK_Thunder::PK_Thunder()
{
	//std::vector<SkillHitbox*> Hitboxlist;

	finished = false;
	//SkillHitbox* newskillhitbox = new SkillHitbox();
	//newskillhitbox->spawndelay = 1;
	//newskillhitbox->hitbox = new Attack_Hitbox();
	//Hitboxlist.push_back(newskillhitbox);

}


PK_Thunder::~PK_Thunder()
{
}

void PK_Thunder::execute(Player& player)
{
	Skill::execute(player);
	mciSendString("close sounds/PK_THUNDER.mp3", NULL, 0, NULL);
	// State version of skill
	///
	/*
	state = new ActiveState();
	state->enter();*/
	///
	//float alpha = 0;		//  alpha<=90 degrees
	float fangle = 0;
	endLag = 10.0f;
	//finished = false;
	// initialize all the hitboxes and adds to the vector

	// FIRST HITBOX
	newhitbox = new Controlled_Projectile_Hitbox(SkillNS::PK_THUNDER_MAX_VEL);
	newhitbox->setAcceleration(SkillNS::PK_THUNDER_ACC);
	newhitbox->setY_Velocity(SkillNS::PK_THUNDER_VEL);

	// create hitbox
	if (!newhitbox->initialize(player.game, 32, 32, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setActive(false);
	newhitbox->setVisible(false);
	
	newhitbox->setFrameDelay(0.05);
	newhitbox->setFrames(28, 31);

	// set hitbox rect
	RECT* hitarea = new RECT();
	hitarea->top = -newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->bottom = newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->left = -newhitbox->getSpriteDataRect().right/2;
	hitarea->right = newhitbox->getSpriteDataRect().right/2;
	newhitbox->setEdge(*hitarea);

	delete hitarea;

	newhitbox->setScale(SkillNS::PK_THUNDER_SCA);
	newhitbox->setKnockbackAngle(finalangle(SkillNS::PK_THUNDER_ANG, player.playerface));
	newhitbox->setDamage(SkillNS::PK_THUNDER_DMG);
	newhitbox->setKnockbackForce(SkillNS::PK_THUNDER_KNB);
	newhitbox->setHitStun(SkillNS::PK_THUNDER_STN);
	newhitbox->setLifetime(SkillNS::PK_THUNDER_LIF);

	// How to push the spawn delay and the hitbox into vector
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.2;
	Hitboxlist.push_back(newskillhitbox);

	mciSendString("play sounds/PK_THUNDER.mp3", NULL, 0, NULL);

}

void PK_Thunder::cancel()
{
	// delete all Hitboxes from list
	// end skill
	Skill::cancel();

	
}


//float PK_Thunder::finalangle(float alpha,int xdirection)	// calculate actual angle based on playerface
//{
//	//  alpha<=90 degrees
//	if (xdirection < 0) { xdirection = -1; }
//	else { xdirection = 1; }
//
//	float finalangle = 90 - (90 - alpha)*(xdirection);
//
//	return finalangle;
//}
