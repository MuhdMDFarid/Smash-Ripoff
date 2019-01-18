#include "Player.h"

//#include <cstdlib>	// for random

Player::Player() : Entity()
{
	spriteData.width = 32;
	spriteData.height = 32;
	radius = 32;
	mass = 0.0f;
	collisionType = entityNS::BOX;
	frameDelay = 0.3f;

	//
	speed = 1000;

	
	//	TEMP code while component implementation is not taught
	movement_component = new Movement_Component();
	canJump = true;

	// END OF TEMP COMPONENT code
}

Player::~Player()
{
}

void Player::draw()
{
	drawProjectiles();
	
	// hitbox_component draw() method-ish
	drawHitboxes();


	Entity::draw();
}

void Player::drawProjectiles()
{
	if (!projectilelist.empty())
	{
		for (int i = 0; i < projectilelist.size(); i++)
		{
			projectilelist[i]->draw();
		}
	}
}

bool Player::initialize(Game*gamePtr, int width, int height, int ncols, TextureManager*textureM)
{
	setFrameDelay(0.3f);
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Player::update(float frameTime) 
{	
	//	Handling the movement

	// using MOVEMENT_COMPONENT
	movement_component->setX_Velocity(movement_component->getX_Velocity() + movement_component->getX_Force()*frameTime);
	movement_component->setY_Velocity(movement_component->getY_Velocity() + movement_component->getY_Force()*frameTime);
	
	// limit maximum velocity
	if (movement_component->getX_Velocity() > MovementNS::MAX_VELOCITY)		// if X velocity reached max towards the right 
	{
		movement_component->setX_Velocity(MovementNS::MAX_VELOCITY);
	}
	else if (movement_component->getX_Velocity() < -MovementNS::MAX_VELOCITY)		// if X velocity reached max towards the left
	{
		movement_component->setX_Velocity(-MovementNS::MAX_VELOCITY);
	}

	//if (movement_component->getY_Velocity() > MovementNS::MAX_VELOCITY)		
	//{
	//	movement_component->setY_Velocity(MovementNS::MAX_VELOCITY);
	//}

	// set coordinates for actual movement
	spriteData.x = spriteData.x + movement_component->getX_Velocity()*frameTime;
	spriteData.y = spriteData.y + movement_component->getY_Velocity()*frameTime;


	//  to make the player loop back on screen
	if (getX() > GAME_WIDTH)
	{
		setX(-getWidth()*getScale());
	}
	else if (getX() < -getWidth()*getScale())
	{
		setX(GAME_WIDTH/2);
	}

	if (getY() > GAME_HEIGHT-getHeight()*getScale())
	{
		setY(GAME_HEIGHT-getHeight()*getScale());
		movement_component->setY_Velocity(0);
		canJump = true;		// reset the jump to enable jump
	}
	else if (getY() < 0)
	{
		setY(0);
		movement_component->setY_Velocity(0);
	}

	Entity::update(frameTime);

	// update projectiles/hitboxes
	updateProjectiles(frameTime);
	updateHitboxes(frameTime);

}

void Player::move(int x_force,int y_force)		// change the force on the char for movement
{
	movement_component->setX_Force(x_force);
	movement_component->setY_Force(y_force);
	//movement_component->addX_Force(x_force);
	//movement_component->addY_Force(y_force);

}


void Player::shoot(Game*gamePtr,int x_target, int y_target, TextureManager *textureM)
{
	newprojectile = new Projectile();

	// create projectile
	if( !newprojectile->initialize(gamePtr,32,32,1,textureM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));

	// set projectile position
	newprojectile->setX(this->getX());
	newprojectile->setY(this->getY());


	// set direction of projectile
	//float angle = atan2(getCenterY() - y_target, getCenterX() - x_target);	// the direction will be opposite for this as the y increases downward
	float angle = atan2(y_target - getCenterY(), x_target - getCenterX());	// in radians

	// 500 is the force multiplier
	newprojectile->setForce(
			500*cos(angle/* - 90 * PI / 180*/),		// x vel
			500*sin(angle/* - 90 * PI / 180*/)		// y vel
		);

	projectilelist.push_back(newprojectile);

}

void Player::updateProjectiles(float frameTime)
{
	// delete projectiles that are out of boundary can be placed in projectile.update()
	for (std::vector<Projectile*>::iterator it = projectilelist.begin(); it != projectilelist.end(); )
	{

		if ((*it)->getX() > GAME_WIDTH || (*it)->getX() < -(*it)->getWidth()/2 || (*it)->getY() > GAME_HEIGHT || (*it)->getY() < -(*it)->getHeight())
		{
			it = deleteProjectile(it);
		}
		else
		{
			it++;
		}
	}

	// update projectiles
	if (!projectilelist.empty())
	{
		for (int i = 0; i < projectilelist.size(); i++)
		{
			projectilelist[i]->update(frameTime);
		}
	}
}

std::vector<Projectile*>::iterator Player::deleteProjectile(std::vector<Projectile*>::iterator it)
{
	SAFE_DELETE(*it);
	return projectilelist.erase(it);

}

void Player::setCollisionType(entityNS::COLLISION_TYPE coltype)
{
	collisionType = coltype;
}

void Player::setJump(bool canjump)
{
	canJump = canjump;
}

void Player::punch(Game * gamePtr, TextureManager * textureM)
{
	newhitbox = new Attack_Hitbox();

	// create hitbox
	if (!newhitbox->initialize(gamePtr, 32, 32, 1, textureM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setScale(5);

	// set hitbox position
	newhitbox->setX(this->getX());
	newhitbox->setY(this->getY());

	hitboxlist.push_back(newhitbox);
}

void Player::drawHitboxes()
{
	if (!hitboxlist.empty())
	{
		for (int i = 0; i < hitboxlist.size(); i++)
		{
			hitboxlist[i]->draw();
		}
	}
}

// Might be better to call the Hitbox_attack components update() which will then handle it's own update()
void Player::updateHitboxes(float frameTime)
{
	// update hitboxes
	if (!hitboxlist.empty())
	{
		for (int i = 0; i < hitboxlist.size(); i++)
		{
			// Hitbox_Attacks should move based on the player
			hitboxlist[i]->setX(getX() + getWidth());
			hitboxlist[i]->setY(getY()+(getHeight() - hitboxlist[i]->getHeight()*hitboxlist[i]->getScale())/2);		//centers the Y coords of hitbox to player

			hitboxlist[i]->update(frameTime);
		}
	}
}

void Player::deleteHitbox()		// deletes all hitboxes for now
{
	if (!hitboxlist.empty())
	{
		for (std::vector<Attack_Hitbox*>::iterator it = hitboxlist.begin(); it != hitboxlist.end(); )
		{
			SAFE_DELETE(*it);
			it=hitboxlist.erase(it);
			
			/*	when scaning through using iterator
			if(condition)
			{
				do something
			}
			else { it++; }		// must always it++ when trying to move to next iterator
			*/
		}
	}
}



