#include "Hunter_NormalS.h"

#include "Hitbox.h"
//#include "Projectile_Hitbox.h"
//#include "ActiveState.h"
//#include "CompletedState.h"
//#include "InactiveState.h"

Hunter_NormalS::Hunter_NormalS()
{
	//std::vector<SkillHitbox*> Hitboxlist;

	finished = false;
	//SkillHitbox* newskillhitbox = new SkillHitbox();
	//newskillhitbox->spawndelay = 1;
	//newskillhitbox->hitbox = new Attack_Hitbox();
	//Hitboxlist.push_back(newskillhitbox);

}


Hunter_NormalS::~Hunter_NormalS()
{
}

void Hunter_NormalS::execute(Player& player)
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
	newhitbox = new Melee_Hitbox();

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
	hitarea->left = -newhitbox->getSpriteDataRect().right;
	hitarea->right = newhitbox->getSpriteDataRect().right;
	newhitbox->setEdge(*hitarea);
	//hitarea = nullptr;
	delete hitarea;

	newhitbox->setDamage(50);

	//alpha = 35;

	newhitbox->setKnockbackAngle(finalangle(35, player.playerface));

	newhitbox->setKnockbackForce(50);
	newhitbox->setHitStun(0.3);

	// How to push the spawn delay and the hitbox into vector
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.2;
	Hitboxlist.push_back(newskillhitbox);

	// SECOND HITBOX
	newhitbox = new Projectile_Hitbox();
	//newhitbox->setX_Velocity(100);
	
	// create hitbox
	if (!newhitbox->initialize(player.game, 32, 32, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setActive(false);
	newhitbox->setVisible(false);

	newhitbox->setFrameDelay(0.05);
	newhitbox->setFrames(28, 31);
	//newhitbox->setCurrentFrame(28);

	hitarea = new RECT();
	hitarea->top = -newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->bottom = newhitbox->getSpriteDataRect().bottom / 2;
	hitarea->left = -newhitbox->getSpriteDataRect().right;
	hitarea->right = newhitbox->getSpriteDataRect().right;
	newhitbox->setEdge(*hitarea);

	newhitbox->setScale(1.5);
	delete hitarea;

	newhitbox->setDamage(1);
	//alpha = 90;
	newhitbox->setKnockbackAngle(finalangle(75,player.playerface));

	newhitbox->setKnockbackForce(420);
	newhitbox->setHitStun(1);
	newhitbox->setLifetime(5);

	// How to push the spawn delay and the hitbox into vector
	newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.5;
	Hitboxlist.push_back(newskillhitbox);
	
}

//void Hunter_NormalS::update(Player& player, float frameTime)
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

void Hunter_NormalS::cancel()
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

//void Hunter_NormalS::draw()
//{
//	for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
//	{
//		(*it)->hitbox->draw();
//		it++;
//	}
//}

//float Hunter_NormalS::finalangle(float alpha,int xdirection)	// calculate actual angle based on playerface
//{
//	//  alpha<=90 degrees
//	if (xdirection < 0) { xdirection = -1; }
//	else { xdirection = 1; }
//
//	float finalangle = 90 - (90 - alpha)*(xdirection);
//
//	return finalangle;
//}
