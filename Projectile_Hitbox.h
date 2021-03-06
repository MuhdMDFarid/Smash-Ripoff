//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _PROJECTILE_HITBOX_H
#define _PROJECTILE_HITBOX_H
#define WIN32_LEAN_AND_MEAN

#include "constants.h"

#include "Hitbox.h"
#include "Movement_Component.h"
#include "Damage_Component.h"
//#include "Player.h"

class Player;

class Projectile_Hitbox : public Hitbox
{
protected:
	float projectileAcceleration = 10.0f;
	float projectileIVelocity = 10.0f;
	Movement_Component * movement_component;	// Movement component to control the forces of movement

public:

	// Constructor
	Projectile_Hitbox();

	// Destructor
	~Projectile_Hitbox();
	
	// ======================
	// Functions
	// ======================
	//virtual void draw();
	//virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);
	void setForce(int x_force, int y_force);

	void setVelocity(int x_velocity, int y_velocity);

	virtual void update(float frameTime,Player& player);
	virtual void collided();
	void activate(Player& player);
	//void remove();
	//void damage(WEAPON weapon);

	void setAcceleration(float acc) { projectileAcceleration = acc; }		// set the Acceleration value of projectile

	void setIVelocity(float iv) { projectileIVelocity = iv; }				// set the Initial Velocity value of projectile 

	// Movement Component controls
	float getX_Velocity() { return movement_component->getX_Velocity(); }
	float getY_Velocity() { return movement_component->getY_Velocity(); }

	float getX_Force() { return movement_component->getX_Force(); }
	float getY_Force() { return movement_component->getY_Force(); }

	void setX_Velocity(float xV) { movement_component->setX_Velocity(xV); }
	void setX_Force(float xF) { movement_component->setX_Force(xF); }

	void setY_Velocity(float yV) { movement_component->setY_Velocity(yV); }
	void setY_Force(float yF) { movement_component->setY_Force(yF); }
};

#endif // _PROJECTILE_H