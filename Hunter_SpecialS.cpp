//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "Hunter_SpecialS.h"

#include "Hitbox.h"
//#include "Projectile_Hitbox.h"
//#include "ActiveState.h"
//#include "CompletedState.h"
//#include "InactiveState.h"

Hunter_SpecialS::Hunter_SpecialS()
{
	finished = false;
}


Hunter_SpecialS::~Hunter_SpecialS()
{
}

void Hunter_SpecialS::execute(Player& player)
{
	Skill::execute(player);


	float fangle = 0;
	endLag = 0.2f;

	// initialize all the hitboxes and adds to the vector

	// FIRST HITBOX
	newhitbox = new Projectile_Hitbox();
	newhitbox->setX_Force(player.playerface*SkillNS::HUNTER_SPEC_ACC);
	newhitbox->setX_Velocity(player.playerface*SkillNS::HUNTER_SPEC_VEL);

	// create hitbox
	if (!newhitbox->initialize(player.game, TILE_SIZE, TILE_SIZE, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setActive(false);
	newhitbox->setVisible(false);

	newhitbox->setFrameDelay(0.05);
	newhitbox->setFrames(28, 31);

	// set hitbox rect
	RECT* hitarea = new RECT();
	hitarea->top = -newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->bottom = newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->left = -newhitbox->getSpriteDataRect().right / 2;
	hitarea->right = newhitbox->getSpriteDataRect().right / 2;
	newhitbox->setEdge(*hitarea);
	//hitarea = nullptr;
	delete hitarea;


	//alpha = 35;
	newhitbox->setScale(SkillNS::HUNTER_SPEC_SCA);
	newhitbox->setKnockbackAngle(finalangle(SkillNS::HUNTER_SPEC_ANG, player.playerface));
	newhitbox->setDamage(SkillNS::HUNTER_SPEC_DMG);
	newhitbox->setKnockbackForce(SkillNS::HUNTER_SPEC_KNB);
	newhitbox->setHitStun(SkillNS::HUNTER_SPEC_STN);
	newhitbox->setLifetime(SkillNS::HUNTER_SPEC_LIF);

	// How to push the spawn delay and the hitbox into vector
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.2;
	Hitboxlist.push_back(newskillhitbox);

}

void Hunter_SpecialS::cancel()
{
	// delete all Hitboxes from list
	// end skill
	Skill::cancel();

	//if (!Hitboxlist.empty())
	//{
	//	for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
	//	{

	//		//SAFE_DELETE((*it)->hitbox);
	//		SAFE_DELETE(*it);
	//		it = Hitboxlist.erase(it);
	//		
	//		//else
	//		//{
	//		//	it++;
	//		//}
	//	}
	//}
	//finished = true;
	
}

//void Skill::completed()
//{
//}

//void Hunter_SpecialS::draw()
//{
//	for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
//	{
//		(*it)->hitbox->draw();
//		it++;
//	}
//}

//float Hunter_SpecialS::finalangle(float alpha,int xdirection)	// calculate actual angle based on playerface
//{
//	//  alpha<=90 degrees
//	if (xdirection < 0) { xdirection = -1; }
//	else { xdirection = 1; }
//
//	float finalangle = 90 - (90 - alpha)*(xdirection);
//
//	return finalangle;
//}
