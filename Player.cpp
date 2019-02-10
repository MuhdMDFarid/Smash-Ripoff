//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "Player.h"

#include "AirborneState.h"
#include "GroundedState.h"

#include "IdleState.h"
#include "AttackState.h"
#include "StaggeredState.h"

// Skill related classes
#include "Skill.h"
#include "Hunter_NormalS.h"
#include "Hunter_SpecialS.h"
#include "PK_Thunder.h"

#include "Controlled_Projectile_Hitbox.h"

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
	playerface = 1;
	
	//	TEMP code for component implementation
	movement_component = new Movement_Component();
	airJump = true;
	jumpcooldown = 0;
	//grounded = false;

	airEnum = STATE_AIRBORNE;
	airborne = new AirborneState();
	airborne->enter(*this);

	actionEnum = STATE_IDLE;
	action = new IdleState();
	// END OF TEMP COMPONENT code

	edge.top = -TILE_SIZE/2;
	edge.bottom = TILE_SIZE / 2;
	edge.left = -TILE_SIZE / 2;
	edge.right = TILE_SIZE / 2;

	skill = new Skill();
	//normals = new Hunter_NormalS();
	//specials = new Hunter_SpecialS();
		
	pk_bind = new PlayerInput_Component();
}

Player::~Player()
{
}

void Player::draw()
{
	drawProjectiles();
	
	// hitbox_component draw() method-ish
	drawHitboxes();

	skill->draw();
	//specials->draw();

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
	// GHETTO
	game = gamePtr;

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
	// TEMP AGILITY POTION THINGY
	if (agilityduration > 0)
	{
		agilityduration -= frameTime;
	}
	else
	{
		speedmultiplier = 1;
	}

	//	Handling the movement

	// using MOVEMENT_COMPONENT
	setY_Velocity(getY_Velocity() + getY_Force()*frameTime);
	/// If the player moving over limit, do not add force. (move to a function)
	// limit maximum velocity
	if (getX_Velocity() < MovementNS::MAX_VELOCITY*speedmultiplier && getX_Force()>=0)		// if X velocity reached max towards the right 
	{
		setX_Velocity(getX_Velocity() + getX_Force()*frameTime);
	}
	else if (getX_Velocity() > -MovementNS::MAX_VELOCITY*speedmultiplier && getX_Force()<=0)		// if X velocity reached max towards the left
	{
		setX_Velocity(getX_Velocity() + getX_Force()*frameTime);
	}
	///


	//if (movement_component->getY_Velocity() > MovementNS::MAX_VELOCITY)		
	//{
	//	movement_component->setY_Velocity(MovementNS::MAX_VELOCITY);
	//}

	// set coordinates for actual movement
	spriteData.x = spriteData.x + getX_Velocity()*frameTime;
	spriteData.y = spriteData.y + getY_Velocity()*frameTime;

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

	if (getY() > GAME_HEIGHT - getHeight()*getScale())
	{
		setY(GAME_HEIGHT - getHeight()*getScale() + 1);
		setY_Velocity(0);
		//airJump = true;		// reset the jump to enable jump
		landed();
	}
	else if (getY() < -(int)GAME_HEIGHT/5)
	{
		setY(-(int)GAME_HEIGHT/5);
	//	setY(0-GAME_HEIGHT*0);
		setY_Velocity(0);
	}
	//////////////////////////

	// State updating
	airborne->update(*this, frameTime);
	action->update(*this, frameTime);

	if (jumpcooldown > 0)
	{
		jumpcooldown -= frameTime;
	}
	else if (jumpcooldown <= 0)		// Replace with else only
	{
		canjump = true;
	}


	Entity::update(frameTime);

	// update projectiles/hitboxes
	//updateProjectiles(frameTime);
	updateHitboxes(frameTime);

	try {
		skill->update(*this, frameTime);
	}
	catch (const std::exception e)
	{
		setActive(false);
	}
}

void Player::move(int x_force,int y_force)		// change the force on the char for movement
{
	setX_Force(x_force);
	setY_Force(y_force);
	//movement_component->addX_Force(x_force);
	//movement_component->addY_Force(y_force);

}


void Player::shoot(Game*gamePtr,int x_target, int y_target, TextureManager *textureM)
{
	newprojectile = new Projectile_Hitbox();

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


std::vector<Projectile_Hitbox*>::iterator Player::deleteProjectile(std::vector<Projectile_Hitbox*>::iterator it)
{
	SAFE_DELETE(*it);
	return projectilelist.erase(it);
}

void Player::setJump(bool canjump)
{
	airJump = canjump;
}

// punch supposedly takes from the moveset
void Player::normalS(/*Game * gamePtr, TextureManager * textureM*/)
{
	// Attack Prototype
	//skill.excecute(*this);
	
	//skill = new Skill();
	Skill* nskill = new Hunter_SpecialS();
	if (nskill != NULL)
	{
		delete skill;
		skill = nskill;
	}
	skill->execute(*this);
	//
}

void Player::specialS()
{
	Skill* nskill = new PK_Thunder();
	//Skill* nskill = new Hunter_SpecialS();
	if (nskill != NULL)
	{
		delete skill;
		skill = nskill;
	}
	skill->execute(*this);
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
			hitboxlist[i]->update(frameTime,*this);
		}
		deleteHitbox();
	}
}

void Player::deleteHitbox()		// deletes all hitboxes for now
{
	if (!hitboxlist.empty())
	{
		for (std::vector<Hitbox*>::iterator it = hitboxlist.begin(); it != hitboxlist.end(); )
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
	PlayerState* astate = new GroundedState();
	airborne->exit(*this);
	delete airborne;
	airborne = astate;
	airborne->enter(*this);
}
void Player::fall()
{
	PlayerState* astate = new AirborneState();
	airborne->exit(*this);
	delete airborne;
	airborne = astate;
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
		action->exit(*this);
		delete action;
		action = astate;
		action->enter(*this);
	}
}

void Player::interrupt(float stunduration)
{
	PlayerState* istate = action->interrupt(*this,stunduration);
	if (istate != NULL)
	{
		action->exit(*this);
		delete action;
		action = istate;
		action->enter(*this);
	}
}

void Player::knockback(float xV,float yV)		// get x/y forces or the hitbox itself
{
	setX_Velocity(xV);
	setY_Velocity(yV);

	//getMovementComponent()->setY_Velocity((*it)->hitbox->getKnockback().y);
}

void Player::hitted(Damage_Component* damageC)		// when player got
{
	float xV = damageC->calculateVector().x/**damage*/;
	float yV = damageC->calculateVector().y/**damage*/;
	
	interrupt(damageC->getStun());
	knockback(xV, yV);
	//damage code to receive damage
	//damagemeter+=damageC->getDamage()
}
