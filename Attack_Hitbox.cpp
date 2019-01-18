#include "Attack_Hitbox.h"



Attack_Hitbox::Attack_Hitbox()
{
}


Attack_Hitbox::~Attack_Hitbox()
{
}

bool Attack_Hitbox::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Attack_Hitbox::draw()
{
	Entity::draw();
}

void Attack_Hitbox::remove()
{
	//SAFE_DELETE(this);
}

void Attack_Hitbox::update(float frameTime)
{
	// Hitbox_Attacks should move based on the player
	Entity::update(frameTime);
}
