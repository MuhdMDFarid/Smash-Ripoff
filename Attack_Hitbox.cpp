#include "Attack_Hitbox.h"



Attack_Hitbox::Attack_Hitbox()
{
	Lifetime = 0.1f;
	Expired = false;
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
	if (getActive())
	{
		if (Lifetime > 0)
		{
			Lifetime -= frameTime;
		}
		if (Lifetime <= 0)
		{
			// delete
			Expired = true;
		}
	}
}

void Attack_Hitbox::collided()
{
	// when hitbox collides
}
