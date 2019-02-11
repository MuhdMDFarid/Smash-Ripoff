#include "meteor.h"
#include <string>
#include <ctime>

Meteor::Meteor() : Entity()
{
	//spriteData.width = meteorNS::WIDTH;
	//spriteData.height = meteorNS::HEIGHT;
	//spriteData.x = meteorNS::X;
	//spriteData.y = meteorNS::Y;
	//spriteData.rect.bottom = getHeight()*getScale();
	//spriteData.rect.right = getWidth()*getScale();
	velocity.x = 0;
	velocity.y = 0;
	radius = meteorNS::WIDTH / 2.0;
	mass = meteorNS::MASS;
	collisionType = entityNS::CIRCLE;
	
	elapsedtime = 10;

	damageC = new Damage_Component();
	damageC->setDamage(60);
	damageC->setAngle(45);
	damageC->setForce(169);
	damageC->setStun(0);
}

bool Meteor::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
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

	srand(time(NULL));
	if (elapsedtime<=0) // if time reaches 0 from 10
	{
		setX(rand() % GAME_WIDTH +GAME_WIDTH/2);
		setY(0);
		elapsedtime = 10;
	}
	elapsedtime -= frameTime;

}
Meteor::~Meteor()
{
}
