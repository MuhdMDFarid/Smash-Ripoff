#ifndef _ATTACK_HITBOX_H               // Prevent multiple definitions if this 
#define _ATTACK_HITBOX_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"

// This is the object generated when a melee/hitbox attack is used
class Attack_Hitbox: public Entity
{
	float Lifetime;		// how long the Hitbox lasts
	bool Expired;

	// Damage_Component* damage_component;		// when the actual damage components get done
public:
	Attack_Hitbox();
	~Attack_Hitbox();
	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);		// initialises a single hitbox
	virtual void draw();
	void remove();
	void update(float frameTime);

	bool isExpired() { return Expired; }


};

#endif