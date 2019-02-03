#include "Player.h"

#include "AirborneState.h"
#include "GroundedState.h"

#include "IdleState.h"
#include "AttackState.h"

//#include "StaggeredState"

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
	airJump = true;
	jumpcooldown = 0;
	//grounded = false;

	airEnum = STATE_AIRBORNE;
	airborne = new AirborneState();

	actionEnum = STATE_IDLE;
	action = new IdleState();
	// END OF TEMP COMPONENT code

	edge.top = -TILE_SIZE/2;
	edge.bottom = TILE_SIZE / 2;
	edge.left = -TILE_SIZE / 2;
	edge.right = TILE_SIZE / 2;
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
	if (Entity::initialize(gamePtr, width, height, ncols, textureM))
	{
		setCollisionType(entityNS::BOX);
		// set the hit box for the player
		edge.top = -height/2;
		edge.bottom = height/2;
		edge.left = -width/2;
		edge.right = width/2;

		return true;
	}
	return false;
}

void Player::update(float frameTime) 
{	
	// GRAVITY SIMULATION
	//if (!grounded)	//grounded is the state if the player is not airborne
	//{
		//movement_component->setY_Velocity(movement_component->getY_Velocity() + GRAVITY * frameTime);
	//}
	//	Handling the movement

	// using MOVEMENT_COMPONENT
	movement_component->setX_Velocity(movement_component->getX_Velocity() + movement_component->getX_Force()*frameTime);
	movement_component->setY_Velocity(movement_component->getY_Velocity() + movement_component->getY_Force()*frameTime);
	

	/// If the player moving over limit, do not add force. (move to a function)
	// limit maximum velocity
	if (movement_component->getX_Velocity() > MovementNS::MAX_VELOCITY)		// if X velocity reached max towards the right 
	{
		movement_component->setX_Velocity(MovementNS::MAX_VELOCITY);
	}
	else if (movement_component->getX_Velocity() < -MovementNS::MAX_VELOCITY)		// if X velocity reached max towards the left
	{
		movement_component->setX_Velocity(-MovementNS::MAX_VELOCITY);
	}
	///


	//if (movement_component->getY_Velocity() > MovementNS::MAX_VELOCITY)		
	//{
	//	movement_component->setY_Velocity(MovementNS::MAX_VELOCITY);
	//}

	// set coordinates for actual movement
	spriteData.x = spriteData.x + movement_component->getX_Velocity()*frameTime;
	spriteData.y = spriteData.y + movement_component->getY_Velocity()*frameTime;

	///////////////////////////////
	//  to make the player loop back on screen may not need in future cos they die
	if (getX() > GAME_WIDTH)
	{
		setX(-getWidth()*getScale());
	}
	else if (getX() < -getWidth()*getScale())
	{
		setX(GAME_WIDTH);
	}

	if (getY() > GAME_HEIGHT-getHeight()*getScale())
	{
		setY(GAME_HEIGHT-getHeight()*getScale()+1);
		movement_component->setY_Velocity(0);
		//airJump = true;		// reset the jump to enable jump
		landed();
	}
	else if (getY() < 0)
	{
		setY(0);
		movement_component->setY_Velocity(0);
	}
	//////////////////////////
	
	// State updating
	airborne->update(*this, frameTime);
	action->update(*this, frameTime);

	jumpcooldown -= frameTime;

	if(jumpcooldown<=0)
		canjump = true;


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

void Player::setJump(bool canjump)
{
	airJump = canjump;
}

void Player::punch(Game * gamePtr, TextureManager * textureM)
{
	////state thing
	//action = new AttackState();
	//action->enter(*this);
	////
	newhitbox = new Attack_Hitbox();

	// create hitbox
	if (!newhitbox->initialize(gamePtr, 32, 32, 1, textureM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	newhitbox->setScale(5);

	// set hitbox position
	newhitbox->setX(getX() + getWidth());
	newhitbox->setY(getY() + (getHeight() - newhitbox->getHeight()*newhitbox->getScale()) / 2);		//centers the Y coords of hitbox to player


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
		deleteHitbox();
	}
}

void Player::deleteHitbox()		// deletes all hitboxes for now
{
	if (!hitboxlist.empty())
	{
		for (std::vector<Attack_Hitbox*>::iterator it = hitboxlist.begin(); it != hitboxlist.end(); )
		{
			if ((*it)->isExpired())
			{
				SAFE_DELETE(*it);
				it = hitboxlist.erase(it);
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
}

void Player::landed()
{
	airborne = new GroundedState();
	airborne->enter(*this);
}
void Player::fall()
{
	airborne = new AirborneState();
	airborne->enter(*this);
	//airEnum = STATE_AIRBORNE;	// should put in GroundedState::enter()
}

void Player::jump()
{
	// DOUBLE JUMP DON'T WROK WHEN ON THE BOTTOM OF SCREEN
	switch (airEnum)
	{
	case STATE_GROUNDED:
		
			//airborne = new AirborneState();
			getMovementComponent()->setY_Velocity(-PlayerNS::JUMP_VELOCITY);
			jumpcooldown = PlayerNS::JUMP_CD;
			canjump = false;
			//airEnum = STATE_AIRBORNE;
			//jumpcooldown = 3;
		
	case STATE_AIRBORNE:
		if (canjump)
		{
			if (airJump)
			{
				getMovementComponent()->setY_Velocity(-PlayerNS::JUMP_VELOCITY);
				airJump = false;
				jumpcooldown = PlayerNS::JUMP_CD;
				canjump = false;
				//jumpcooldown = 2;
			}
		}
	}
}// End of Jump

void Player::handleInput(Input* input)
{
	// What if the input doesn't need to delete the state cos no transition
	PlayerState* airstate = airborne->handleInput(*this, input);
	//throw(GameError(gameErrorNS::FATAL_ERROR, typeid(*airborne).name() ));
	if (airstate != NULL)		// if new state not null and if new state not the same
	{
		airborne->exit(*this);
		delete airborne;
		airborne = airstate;
		airborne->enter(*this);
	}

	PlayerState* astate = action->handleInput(*this,input);
	if (astate != NULL)
	{
		airborne->exit(*this);
		delete action;
		action = astate;
		action->enter(*this);
	}
}

