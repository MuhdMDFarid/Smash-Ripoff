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
private:
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

	void update(float frameTime,Player& player);
	void collided();
	void activate(Player& player);
	//void remove();
	//void damage(WEAPON weapon);

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