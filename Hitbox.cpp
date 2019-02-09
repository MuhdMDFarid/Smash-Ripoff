#include "Hitbox.h"

#include "Player.h"

Hitbox::Hitbox()
{
	Lifetime = 0.1f;
	Expired = false;
	collisionType = entityNS::BOX;

	spriteData.width = 32;
	spriteData.height = 32;
	spriteData.x = 0;
	spriteData.y = 0;

	edge.top = -TILE_SIZE / 2;
	edge.bottom = TILE_SIZE / 2;
	edge.left = -TILE_SIZE / 2;
	edge.right = TILE_SIZE / 2;

	damage_component = new Damage_Component();
}


Hitbox::~Hitbox()
{
}

bool Hitbox::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Hitbox::draw()
{
	Entity::draw();
}

void Hitbox::remove()
{
	//delete this;
}

void Hitbox::update(float frameTime,Player& player)
{
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

void Hitbox::activate(Player& player)
{
	// set hitbox to active
	setVisible(true);
	setActive(true);
	player.hitboxlist.push_back(this);
}
