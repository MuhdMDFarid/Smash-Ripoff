//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _MELEE_HITBOX_H               // Prevent multiple definitions if this 
#define _MELEE_HITBOX_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Hitbox.h"
#include "Damage_Component.h"
//#include "Player.h"

class Player;

// This is the object generated when a melee/hitbox attack is used
class Melee_Hitbox : public Hitbox
{
	//float Lag;			// how long before the Hitbox spawns?
	//float Lifetime;		// how long the Hitbox lasts
	//bool Expired;

	//// hit box spawn distance vector x,y thing

	//Damage_Component* damage_component;		// when the actual damage components get done

public:
	Melee_Hitbox();
	~Melee_Hitbox();
	//bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);		// initialises a single hitbox
	//void draw();
	//void remove();
	void update(float frameTime,Player& player);
	void collided();
	void activate(Player& player);

	//Damage_Component* getDamageC() { return damage_component; }
	//D3DXVECTOR2 getKnockback() { return damage_component->calculateVector(); }
	//float getDamage() { return damage_component->getDamage(); }
	//float getStun() { return damage_component->getStun(); }
	//float getLifetime() { return Lifetime; }

	//void setDamage(float dmg) { damage_component->setDamage(dmg); }
	//void setKnockbackAngle(float ang) { damage_component->setAngle(ang); }
	//void setKnockbackForce(float N) { damage_component->setForce(N); }
	//void setHitStun(float stn) { damage_component->setStun(stn); }
	//void setLifetime(float lifetime) { Lifetime = lifetime; }

	//Damage_Component* getDamageComp() { return damage_component; }

};

#endif // _ATTACK_HITBOX_H