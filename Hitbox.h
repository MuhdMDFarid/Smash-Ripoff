//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _HITBOX_H               // Prevent multiple definitions if this 
#define _HITBOX_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"
#include "Damage_Component.h"
//#include "Player.h"

class Player;

class Hitbox : public Entity
{
protected:
	float Lifetime;							// how long the Hitbox lasts
	bool Expired;							// if Hitbox needs to be deleted
	Damage_Component* damage_component;		// where the damage and knockback info

public:
	Hitbox();
	~Hitbox();

	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);		// initialises a single hitbox
	void draw();
	virtual void remove();
	virtual void update(float frameTime, Player& player);
	virtual void collided() {};		// when hitbox collides
	virtual void activate(Player& player);
	bool isExpired() { return Expired; }


	Damage_Component* getDamageC() { return damage_component; }
	D3DXVECTOR2 getKnockback() { return damage_component->calculateVector(); }
	float getDamage() { return damage_component->getDamage(); }
	float getStun() { return damage_component->getStun(); }
	float getLifetime() { return Lifetime; }

	void setDamage(float dmg) { damage_component->setDamage(dmg); }
	void setKnockbackAngle(float ang) { damage_component->setAngle(ang); }
	void setKnockbackForce(float N) { damage_component->setForce(N); }
	void setHitStun(float stn) { damage_component->setStun(stn); }
	void setLifetime(float lifetime) { Lifetime = lifetime; }

	virtual float getX_Velocity() { return NULL; }
	virtual float getY_Velocity() { return NULL; }

	virtual float getX_Force() { return NULL; }
	virtual float getY_Force() { return NULL; }

	virtual void setX_Velocity(float xV) {};
	virtual void setX_Force(float xF) {};

	virtual void setY_Velocity(float yV) {};
	virtual void setY_Force(float yF) {};

	virtual void setAcceleration(float acc) {};		// set the Acceleration value of projectile
	virtual void setIVelocity(float iv) {};			// set the Initial Velocity value of projectile 

};
#endif