#ifndef _ATTACK_HITBOX_H               // Prevent multiple definitions if this 
#define _ATTACK_HITBOX_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"
#include "Damage_Component.h"

// This is the object generated when a melee/hitbox attack is used
class Attack_Hitbox : public Entity
{
	//float Lag;			// how long before the Hitbox spawns?
	float Lifetime;		// how long the Hitbox lasts
	bool Expired;

	Damage_Component* damage_component;		// when the actual damage components get done

public:
	Attack_Hitbox();
	~Attack_Hitbox();
	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);		// initialises a single hitbox
	virtual void draw();
	void remove();
	void update(float frameTime);
	void collided();

	bool isExpired() { return Expired; }

	D3DXVECTOR2 getKnockback() { return damage_component->calculateVector(); }
	float getDamage() { return damage_component->getDamage(); }
	float getStun() { return damage_component->getStun(); }

	void setDamage(float dmg) { damage_component->setDamage(dmg); }
	void setKnockbackAngle(float ang) { damage_component->setAngle(ang); }
	void setKnockbackForce(float N) { damage_component->setForce(N); }
	void setHitStun(float stn) { damage_component->setStun(stn); }

	//Damage_Component* getDamageComp() { return damage_component; }

};

#endif // _ATTACK_HITBOX_H