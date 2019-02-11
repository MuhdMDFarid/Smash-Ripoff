//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "PK_Fire.h"

//#include "ActiveState.h"
//#include "CompletedState.h"
//#include "InactiveState.h"

PK_Fire::PK_Fire()
{
	//std::vector<SkillHitbox*> Hitboxlist;

	finished = false;
	//SkillHitbox* newskillhitbox = new SkillHitbox();
	//newskillhitbox->spawndelay = 1;
	//newskillhitbox->hitbox = new Attack_Hitbox();
	//Hitboxlist.push_back(newskillhitbox);

}


PK_Fire::~PK_Fire()
{
}

void PK_Fire::execute(Player& player)
{
	Skill::execute(player);
	mciSendString("close sounds/PK_FIRE.mp3", NULL, 0, NULL);

	// State version of skill
	///
	/*
	state = new ActiveState();
	state->enter();*/
	///
	//float alpha = 0;		//  alpha<=90 degrees
	float fangle = 0;
	endLag = 0.75f;
	int projectiles = 3;
	// initialize all the hitboxes and adds to the vector
	for (int i = 0; i < projectiles;i++ )
	{
		newhitbox = new Projectile_Hitbox();

		// set movement of projectile
		newhitbox->setX_Velocity((SkillNS::PK_FIRE_XVEL +i*SkillNS::PK_FIRE_VELCHNG)* player.playerface);
		newhitbox->setY_Velocity(-(SkillNS::PK_FIRE_YVEL+i*SkillNS::PK_FIRE_VELCHNG));
		newhitbox->setY_Force(GRAVITY);

		// create hitbox
		if (!newhitbox->initialize(player.game, TILE_SIZE, TILE_SIZE, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
		newhitbox->setActive(false);
		newhitbox->setVisible(false);

		newhitbox->setFrameDelay(0.05);
		newhitbox->setFrames(28, 31);
		//newhitbox->setCurrentFrame(28);

		RECT* hitarea = new RECT();
		hitarea->top = -newhitbox->getSpriteDataRect().bottom / 2;
		hitarea->bottom = newhitbox->getSpriteDataRect().bottom / 2;
		hitarea->left = -newhitbox->getSpriteDataRect().right / 2;
		hitarea->right = newhitbox->getSpriteDataRect().right / 2;
		newhitbox->setEdge(*hitarea);

		newhitbox->setScale(SkillNS::PK_FIRE_SCA);
		delete hitarea;

		newhitbox->setKnockbackAngle(finalangle(SkillNS::PK_FIRE_ANG, player.playerface));
		newhitbox->setDamage(SkillNS::PK_FIRE_DMG);
		newhitbox->setKnockbackForce(SkillNS::PK_FIRE_KNB);
		newhitbox->setHitStun(SkillNS::PK_FIRE_STN);
		newhitbox->setLifetime(SkillNS::PK_FIRE_LIF);
		// How to push the spawn delay and the hitbox into vector
		SkillHitbox* newskillhitbox = new SkillHitbox();
		newskillhitbox->hitbox = newhitbox;
		newskillhitbox->spawndelay = 0.75;
		Hitboxlist.push_back(newskillhitbox);
	}
	mciSendString("play sounds/PK_FIRE.mp3", NULL, 0, NULL);

}

void PK_Fire::cancel()
{
	// delete all Hitboxes from list
	// end skill
	Skill::cancel();
	
}