#include "meteor.h"

Meteor::Meteor() : Entity()
{
	spriteData.width = meteorNS::WIDTH;
	spriteData.height = meteorNS::HEIGHT;
	spriteData.x = meteorNS::X;
	spriteData.y = meteorNS::Y;
	spriteData.rect.bottom = meteorNS::HEIGHT;
	spriteData.rect.right = meteorNS::WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	radius = meteorNS::WIDTH / 2.0;
	mass = meteorNS::MASS;
	collisionType = entityNS::CIRCLE;
}

bool Meteor::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

void Meteor::draw()
{
	Image::draw();
	// if(isCollided)
	// meteor.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

void Meteor::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * meteorNS::ROTATION_RATE;  // rotate the meteor
	spriteData.x += frameTime * velocity.x;         // move meteor along X 
	spriteData.y += frameTime * velocity.y;         // move meteor along Y

	// Deallocate once it goes off screen?
	if (spriteData.x > GAME_WIDTH - meteorNS::WIDTH) // if goes off screen right
	{
		this->setScale(0);
		this->setActive(false);
	}
	else if (spriteData.x < 0) // if goes off screen left
	{
		this->setScale(0);
		this->setActive(false);
	}
	if (spriteData.y > GAME_HEIGHT - meteorNS::HEIGHT) // if goes off screen bottom
	{
		this->setScale(0);
		this->setActive(false);
	}
	else if (spriteData.y < 0) // if goes off screen top
	{
		this->setScale(0);
		this->setActive(false);
	}


}
Meteor::~Meteor()
{
}
