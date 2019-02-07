#include "Skill.h"

//#include "ActiveState.h"
//#include "CompletedState.h"
//#include "InactiveState.h"

Skill::Skill()
{
	//std::vector<SkillHitbox*> Hitboxlist;

	finished = false;
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->spawndelay = 1;
	newskillhitbox->hitbox = new Attack_Hitbox();
	Hitboxlist.push_back(newskillhitbox);

	//newskillhitbox = NULL;
	//newskillhitbox->hitbox = nullptr;
	//newskillhitbox->spawndelay = 0;
}


Skill::~Skill()
{
}

void Skill::execute(Player& player)
{
	// State version of skill
	///
	/*
	state = new ActiveState();
	state->enter();*/
	///
	finished = false;
	// initialize all the hitboxes and adds to the vector
	newhitbox = new Attack_Hitbox();

	// create hitbox
	if (!newhitbox->initialize(player.game, 32, 32, PlayerNS::TEXTURE_COLS, player.getTextureManager()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setActive(false);
	newhitbox->setVisible(false);
	//newhitbox->setScale(5);
	newhitbox->setFrameDelay(0.05);
	newhitbox->setFrames(28, 31);
	newhitbox->setCurrentFrame(28);

	newhitbox->setDamage(50);
	newhitbox->setKnockbackAngle(35+90);
	newhitbox->setKnockbackForce(500);

	// How to push the spawn delay and the hitbox into vector
	SkillHitbox* newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.2;
	Hitboxlist.push_back(newskillhitbox);

	newhitbox = new Attack_Hitbox();

	// create hitbox
	if (!newhitbox->initialize(player.game, 32, 32, 4, player.getTextureManager()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setActive(false);
	newhitbox->setVisible(false);
	//newhitbox->setScale(5);
	newhitbox->setFrameDelay(0.05);
	newhitbox->setFrames(28, 31);
	newhitbox->setCurrentFrame(28);

	newhitbox->setDamage(10);
	newhitbox->setKnockbackAngle(90);
	newhitbox->setKnockbackForce(1000);

	// How to push the spawn delay and the hitbox into vector
	newskillhitbox = new SkillHitbox();
	newskillhitbox->hitbox = newhitbox;
	newskillhitbox->spawndelay = 0.5;
	Hitboxlist.push_back(newskillhitbox);
	
}

void Skill::update(Player& player, float frameTime)
{
	if (!Hitboxlist.empty())
	{
		for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
		{
			if((*it)->spawndelay<=0)
			{
				if (!(*it)->hitbox->getActive()) 
				{ 
					(*it)->hitbox->setVisible(true);
					(*it)->hitbox->setActive(true);
				}	// set hitbox to active

				(*it)->hitbox->setX(player.getX() + ((*it)->hitbox->getWidth()*(*it)->hitbox->getScale())*player.playerface);

				(*it)->hitbox->setY(player.getCenterY() - ((*it)->hitbox->getHeight()*(*it)->hitbox->getScale()) / 2);		//centers the Y coords of hitbox to player

			}

			else if ((*it)->spawndelay > 0)			// updating spawn delay
			{
				(*it)->spawndelay -= frameTime;
			}

			(*it)->hitbox->update(frameTime);

			if ((*it)->hitbox->isExpired())
			{
				//SAFE_DELETE((*it)->hitbox);
				SAFE_DELETE(*it);
				it = Hitboxlist.erase(it);
			}
			else
			{
				it++;
			}
			/*	when scaning through using iterator
			if(condition)
			{
				do something
			}
			else { it++; }		// must always it++ when trying to move to next iterator
			*/
		}
	}
	else
	{
		finished = true;
	}
}

void Skill::cancel()
{
	// delete all Hitboxes from list
	// end skill
}

//void Skill::completed()
//{
//}

void Skill::draw()
{
	for (std::vector<SkillHitbox*>::iterator it = Hitboxlist.begin(); it != Hitboxlist.end(); )
	{
		(*it)->hitbox->draw();
		it++;
	}
}
