#include "attackHitbox.h"


attackHitbox::attackHitbox()
{
}

attackHitbox::~attackHitbox()
{
}

bool attackHitbox::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void attackHitbox::draw()
{
	Entity::draw();
}

void attackHitbox::remove()
{
	//SAFE_DELETE(this);
}

void attackHitbox::update(float frameTime)
{
	// Hitbox_Attacks should move based on the player
	Entity::update(frameTime);
}