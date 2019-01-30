#ifndef _Player_H
#define _Player_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>
//#include"ship.h"

#include "Projectile.h"
#include "Movement_Component.h"
#include "attackHitbox.h"
#include "PlayerState.h"
#include "AirborneState.h"
#include "GroundedState.h"

namespace PlayerNS
{
	//int WIDTH = 64;
	//int HEIGHT = 64;
	const int TEXTURE_COLS = 4;
	const float PLAYER_MOVE_DELAY = 0.2f;
	
}

class Player : public Entity
{
private:

	float speed;
	float viewAngleOffset;
	float moveDelay = 0;
	
	Movement_Component * movement_component;	// Movement component to control the forces of movement
	//std::vector<Projectile*> projectilelist;
	bool canJump;
	
public:

	// Constructor
	Player();

	// Destructor
	~Player();

	// ======================
	// Functions
	// ======================
	virtual bool initialize(Game*gamePtr, int width, int height, int ncols, TextureManager*textureM);
	float getSpeed() { return speed; }
	void move(int x_force, int y_force);	// change the forces on the char for movement
	virtual void draw();
	void drawProjectiles();
	void update(float frameTime);

	//void setCollisionType(entityNS::COLLISION_TYPE coltype);

	// Components and added stuff
	bool grounded;		// replaced to a state in future
	//AirborneState* airborne;

	Projectile *newprojectile;		// not sure if this should be done
	std::vector<Projectile*> projectilelist;

	// hitbox_attack components stuff
	std::vector<attackHitbox*> hitboxlist;		// this should be placed in a hitbox_attack component
	attackHitbox *newhitbox;		// this should be placed in a hitbox_attack

	Movement_Component* getMovementComponent() { return movement_component; }
	bool iscanJump() { return canJump; }
	void setJump(bool canjump);

	// should consider placing this somewhere projectile related
	void shoot(Game*gamePtr, int x_target, int y_target, TextureManager*textureM);
	void updateProjectiles(float frameTime);
	std::vector<Projectile*>::iterator deleteProjectile(std::vector<Projectile*>::iterator it);

	// melee/hitbox attack prototype
	void punch(Game*gamePtr, TextureManager*textureM);
	void drawHitboxes();
	void updateHitboxes(float frameTime);
	void deleteHitbox();

};

#endif // _PLAYER_H