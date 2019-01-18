
#include "Projectile.h"

Projectile::Projectile() : Entity()
{
	spriteData.width = 32;
	spriteData.height = 32;
	spriteData.x = 0;
	spriteData.y = 0;
	movement_component = new Movement_Component();

}

Projectile::~Projectile()
{
}

void Projectile::draw()
{
	Entity::draw();
}

bool Projectile::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
	
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Projectile::setForce(int x_force, int y_force)
{
	movement_component->setX_Force(x_force);
	movement_component->setY_Force(y_force);
}

void Projectile::update(float frameTime)
{
	Entity::update(frameTime);

	// using MOVEMENT_COMPONENT
	movement_component->setX_Velocity(movement_component->getX_Velocity() + movement_component->getX_Force()*frameTime);
	movement_component->setY_Velocity(movement_component->getY_Velocity() + movement_component->getY_Force()*frameTime);
	
	//  to make the projectile disappear at screen boundary
	if (getX() > GAME_WIDTH)
	{
		remove();
	}
	else if (getX() < -getWidth()*getScale())
	{
		remove();
	}

	if (getY() > GAME_HEIGHT - getHeight()*getScale())
	{
		remove();
	}
	else if (getY() < 0)
	{
		remove();
	}

	// set coordinates for actual movement
	spriteData.x = spriteData.x + movement_component->getX_Velocity()*frameTime;
	spriteData.y = spriteData.y + movement_component->getY_Velocity()*frameTime;

	//
}
void Projectile::remove()
{
	//SAFE_DELETE(this);
}
//
//void Projectile::damage(WEAPON weapon)
//{
//
//}
