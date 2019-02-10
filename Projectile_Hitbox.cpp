#include "Projectile_Hitbox.h"
#include "Player.h"
//class Player;

Projectile_Hitbox::Projectile_Hitbox() : Hitbox::Hitbox()
{

	movement_component = new Movement_Component();
	//setX_Force(projectileAcceleration);
	//setX_Velocity(projectileIVelocity);
}

Projectile_Hitbox::~Projectile_Hitbox()
{
}

//void Projectile_Hitbox::draw()
//{
//	Entity::draw();
//}

//bool Projectile_Hitbox::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
//{
//	
//	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
//}

void Projectile_Hitbox::setForce(int x_force, int y_force)
{
	setX_Force(x_force);
	setY_Force(y_force);
}

void Projectile_Hitbox::setVelocity(int x_velocity, int y_velocity)
{
	setX_Velocity(x_velocity);
	setY_Velocity(y_velocity);
}

void Projectile_Hitbox::update(float frameTime,Player& player)
{
	//Hitbox::update(frameTime);
	if (getActive())
	{
		// using MOVEMENT_COMPONENT
		setX_Velocity(getX_Velocity() + getX_Force()*frameTime);
		setY_Velocity(getY_Velocity() + getY_Force()*frameTime);

		// set coordinates for actual movement
		spriteData.x = spriteData.x + getX_Velocity()*frameTime;
		spriteData.y = spriteData.y + getY_Velocity()*frameTime;

		//  to make the projectile disappear at screen boundary
		if (getX() > GAME_WIDTH)
		{
			//remove();
			Expired = true;
		}
		else if (getX() < -getWidth()*getScale())
		{
			//remove();
			Expired = true;
		}
		else if (getY() > GAME_HEIGHT - getHeight()*getScale())
		{
			//remove();
			Expired = true;
		}
		else if (getY() < 0)
		{
			//remove();
			Expired = true;
		}
	}
	Hitbox::update(frameTime, player);
}

void Projectile_Hitbox::collided()		//when projectile collides
{
	Expired = true;
}

void Projectile_Hitbox::activate(Player& player)
{
	Hitbox::activate(player);
	setVisible(true);
	//setX_Force(projectileAcceleration*player.playerface);
	//setX_Velocity(getX_ve*player.playerface);
	setCenterX(player.getCenterX());
	setCenterY(player.getCenterY());
}

//void Projectile_Hitbox::remove()
//{
//	//SAFE_DELETE(this);
//}

//void Projectile::damage(WEAPON weapon)
//{
//
//}