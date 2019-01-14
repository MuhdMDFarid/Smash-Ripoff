#include "Player.h"


Player::Player() : Entity()
{
	spriteData.width = 32;
	spriteData.height = 32;
	radius = 32;
	mass = 0.0f;
	collisionType = entityNS::BOX;
	frameDelay = 0.3f;

	//
	speed = 500;

	
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
	if (movement_component->getX_Velocity() > MovementNS::MAX_VELOCITY)		if // 
	{
		movement_component->setX_Velocity(MovementNS::MAX_VELOCITY);
	}
	if (movement_component->getY_Velocity() > MovementNS::MAX_VELOCITY)
	{
		movement_component->setY_Velocity(MovementNS::MAX_VELOCITY);
	}

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

	// update projectiles
	if (!projectilelist.empty())
	{
		for (int i = 0; i < projectilelist.size(); i++)
		{
			projectilelist[i]->update(frameTime);
		}
	}

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
	float angle = atan2(y_target - getCenterY(), x_target - getCenterX());

	// 200 is the force multiplier
	newprojectile->setForce(
			500*cos(angle/* - 90 * PI / 180*/),		// x vel
			500*sin(angle/* - 90 * PI / 180*/)		// y vel
		);
	projectilelist.push_back(newprojectile);

	//graphics->spriteBegin();
	//projectile.draw();
	//graphics->spriteEnd();
	
}


void Player::setCollisionType(entityNS::COLLISION_TYPE coltype)
{
	collisionType = coltype;
}

void Player::setJump(bool canjump)
{
	canJump = canjump;
}



