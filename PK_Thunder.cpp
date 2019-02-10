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

	// State version of skill
	///
	/*
	state = new ActiveState();
	state->enter();*/
	///
	//float alpha = 0;		//  alpha<=90 degrees
	float fangle = 0;
	endLag = 0.5f;
	//finished = false;
	// initialize all the hitboxes and adds to the vector

	// FIRST HITBOX
	newhitbox = new Controlled_Projectile_Hitbox();
	newhitbox->setAcceleration(500);
	newhitbox->setY_Velocity(-400);

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
	//hitarea = nullptr;
	delete hitarea;

	newhitbox->setDamage(50);

	//alpha = 35;

	newhitbox->setKnockbackAngle(finalangle(35, player.playerface));

	newhitbox->setKnockbackForce(50);
	newhitbox->setHitStun(0.3);
	newhitbox->setLifetime(15);

	// How to push the spawn delay and the hitbox into vector
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.2;
	Hitboxlist.push_back(newskillhitbox);

	
}

//void PK_Thunder::update(Player& player, float frameTime)
//{
//	if (!Hitboxlist.empty())
//	{
//		for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
//		{
//			(*it)->hitbox->update(frameTime, player);
//
//			if((*it)->spawndelay<=0)
//			{
//				if (!(*it)->hitbox->getActive()) 
//				{ 
//					// set hitbox to active
//					(*it)->hitbox->activate(player);
//
//				}					
//				// Sets the X coords of the hitbox based on the direction player faces
//				//(*it)->hitbox->setCenterX(player.getCenterX()+(player.playerface)*(*it)->hitbox->getEdge().right*(*it)->hitbox->getScale());
//				//(*it)->hitbox->update(frameTime,player);
//				// Sets the Y coords of the hitbox based on the center of the player
//				//(*it)->hitbox->setCenterY(player.getCenterY());						//centers the Y coords of hitbox to player
//
//			}
//
//			else if ((*it)->spawndelay > 0)			// updating spawn delay
//			{
//				(*it)->spawndelay -= frameTime;
//			}
//
//
//			if ((*it)->hitbox->getActive())
//			{
//				//SAFE_DELETE(*it);
//				it = Hitboxlist.erase(it);
//			}
//			else
//			{
//				it++;
//			}
//		}
//	}
//	else if(endLag>0)
//	{
//		endLag -= frameTime;
//	}
//	else
//	{
//		finished = true;
//	}
//}

void PK_Thunder::cancel()
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

//void PK_Thunder::draw()
//{
//	for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
//	{
//		(*it)->hitbox->draw();
//		it++;
//	}
//}

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
