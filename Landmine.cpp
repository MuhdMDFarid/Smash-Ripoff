#include "Landmine.h"

#include "AirborneState.h"
#include "GroundedState.h"

#include "IdleState.h"
Landmine::Landmine() :Entity()
{
	collisionType = entityNS::BOX;
	//set the hit box of the platform
	edge.top = -LANDMINE_SIZE / 2;
	edge.bottom = LANDMINE_SIZE / 2;
	edge.left = -LANDMINE_SIZE / 2;
	edge.right = LANDMINE_SIZE / 2;

	spriteData.width = LANDMINE_SIZE;
	spriteData.height = LANDMINE_SIZE;
	mass = 1000;
}


Landmine::~Landmine()
{
}

bool Landmine::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	if (Entity::initialize(gamePtr, width, height, ncols, textureM))
	{
		//setCollisionType(entityNS::BOX);
		//set the hit box of the platform
		edge.top = -height / 2;
		edge.bottom = height / 2;
		edge.left = -width / 2;
		edge.right = width / 2;

		spriteData.width = width;
		spriteData.height = height;
		//setMass(1000);
		return true;
	}
	return false;

}

void Landmine::draw()
{
	Entity::draw();
}

void Landmine::update(float frameTime)
{
	Entity::update(frameTime);
}