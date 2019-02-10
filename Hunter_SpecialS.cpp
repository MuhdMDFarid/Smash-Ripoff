#include "Hunter_SpecialS.h"

//#include "ActiveState.h"
//#include "CompletedState.h"
//#include "InactiveState.h"

Hunter_SpecialS::Hunter_SpecialS()
{
	//std::vector<SkillHitbox*> Hitboxlist;

	finished = false;
	//SkillHitbox* newskillhitbox = new SkillHitbox();
	//newskillhitbox->spawndelay = 1;
	//newskillhitbox->hitbox = new Attack_Hitbox();
	//Hitboxlist.push_back(newskillhitbox);

}


Hunter_SpecialS::~Hunter_SpecialS()
{
}

void Hunter_SpecialS::execute(Player& player)
{
	Skill::execute(player);

	// State version of skill
	///
	/*
	state = new ActiveState();
	state->enter();*/
	///
	//float alpha = 0;		//  alpha<=90 degrees
	float fangle = 0;
	endLag = 0.75f;

	// initialize all the hitboxes and adds to the vector

	newhitbox = new Projectile_Hitbox();
	
	// set movement of projectile
	newhitbox->setX_Velocity(200 * player.playerface);
	//newhitbox->setX_Force(100 * player.playerface);
	newhitbox->setY_Velocity(-500);
	newhitbox->setY_Force(GRAVITY);

	// create hitbox
	if (!newhitbox->initialize(player.game, 32, 32, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setActive(false);
	newhitbox->setVisible(false);

	newhitbox->setFrameDelay(0.05);
	newhitbox->setFrames(28, 31);
	//newhitbox->setCurrentFrame(28);

	RECT* hitarea = new RECT();
	hitarea->top = -newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->bottom = newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->left = -newhitbox->getSpriteDataRect().right/2;
	hitarea->right = newhitbox->getSpriteDataRect().right/2;
	newhitbox->setEdge(*hitarea);

	newhitbox->setScale(1.5);
	delete hitarea;

	newhitbox->setDamage(1);
	//alpha = 90;
	newhitbox->setKnockbackAngle(finalangle(90,player.playerface));

	newhitbox->setKnockbackForce(1069);
	newhitbox->setHitStun(0.75);
	newhitbox->setLifetime(15);

	// How to push the spawn delay and the hitbox into vector
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.75;
	Hitboxlist.push_back(newskillhitbox);
	
}

void Hunter_SpecialS::cancel()
{
	// delete all Hitboxes from list
	// end skill
	Skill::cancel();
	
}