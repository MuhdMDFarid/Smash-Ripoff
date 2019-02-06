#include "Platform.h"


Platform::Platform():Entity()
{
	collisionType = entityNS::BOX;
	//set the hit box of the platform
	edge.top = -TILE_SIZE/2;
	edge.bottom = TILE_SIZE / 2;
	edge.left = -TILE_SIZE / 2;
	edge.right = TILE_SIZE / 2;

	spriteData.width = TILE_SIZE;
	spriteData.height = TILE_SIZE;
	mass=1000;
}


Platform::~Platform()
{
}

bool Platform::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
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

void Platform::draw()
{
	Entity::draw();
}

void Platform::update(float frameTime)
{
	Entity::update(frameTime);
}

void Platform::updateUp(float frameTime)
{
	Entity::update(frameTime);

	//hk
	spriteData.y += frameTime * velocity.y;
	spriteData.x += frameTime * velocity.x;
	if (spriteData.y + TILE_SIZE < 0)
	{
		spriteData.y = GAME_HEIGHT;
	}
}

void Platform::updateDown(float frameTime)
{
	Entity::update(frameTime);

	//hk
	spriteData.y += frameTime * velocity.y;
	spriteData.x += frameTime * velocity.x;
	if (spriteData.y > GAME_HEIGHT)
	{
		spriteData.y = -TILE_SIZE;
	}
}