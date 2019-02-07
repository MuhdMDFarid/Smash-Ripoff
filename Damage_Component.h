#ifndef _DAMAGE_COMPONENT_H               // Prevent multiple definitions if this 
#define _DAMAGE_COMPONENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Component.h"
//#include <cmath>
#include <d3dx9math.h>
#include "constants.h"
//
//#include "entity.h"
//#include <vector>

class Damage_Component : public Component
{
private:
	float damage;
	float angle;
	float force;
	float stun;
public:
	Damage_Component();
	~Damage_Component();

	// ======================
	// Functions
	// ======================
	float getDamage() { return damage; }
	float getAngle() { return angle; }
	float getForce() { return force; }
	float getStun() { return stun; }

	void setDamage(float dmg) { damage = dmg; }
	void setAngle(float ang) { angle = ang; }
	void setForce(float N) { force = N; }
	void setStun(float stn) { stun = stn; }

	D3DXVECTOR2 calculateVector();

	virtual void receive(int message);
	virtual void execute();

};

#endif