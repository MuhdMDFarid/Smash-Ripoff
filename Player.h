#ifndef _Player_H
#define _Player_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>
//#include"ship.h"

#include "Projectile.h"
#include "Movement_Component.h"
#include "Attack_Hitbox.h"


enum State
{
	STATE_GROUNDED,
	STATE_AIRBORNE,
	STATE_STAGGERED,
	STATE_ATTACK,
	STATE_IDLE
};

class PlayerState;		// forward declaration
class Skill;
//class SkillHitbox;

namespace PlayerNS
{
	//int WIDTH = 64;
	//int HEIGHT = 64;
	const int TEXTURE_COLS = 4;
	const float PLAYER_MOVE_DELAY = 0.2f;

	const float JUMP_CD = 0.5f;
	const int JUMP_VELOCITY = 500;

	// Player 1 Frames
	const int P1_IDLE_START = 0;
	const int P1_IDLE_END = 3;

	const int P1_MOVE_START = 4;
	const int P1_MOVE_END = 7;

	const int P1_ATTACK_START = 8;
	const int P1_ATTACK_END = 11;

	const int P1_AIRBORNE_START = 12;
	const int P1_AIRBORNE_END = 15;

	const int P1_SLAM_START = 20;
	const int P1_SLAM_END = 23;
	
}

class Player : public Entity
{
private:

	float speed;
	float viewAngleOffset;
	float moveDelay = 0;
	
	Movement_Component * movement_component;	// Movement component to control the forces of movement
	//std::vector<Projectile*> projectilelist;
	
public:
	//bool grounded;		// replaced to a state in future
	void landed();
	void fall();
	void jump();
	void interrupt();
	State airEnum;
	PlayerState* airborne;
	State actionEnum;
	PlayerState* action;
	float jumpcooldown;
	bool airJump;
	bool canjump;

	int playerface;

	// GHETTO
	Game* game = nullptr;
	TextureManager* getTextureManager() { return textureManager; }

	void handleInput(Input* input);


	Projectile *newprojectile;		// not sure if this should be done
	std::vector<Projectile*> projectilelist;

	// hitbox_attack components stuff
	std::vector<Attack_Hitbox*> hitboxlist;		// this should be placed in a hitbox_attack component
	Attack_Hitbox *newhitbox;		// this should be placed in a hitbox_attack
	
	Skill* skill;
	//std::vector<SkillHitbox*> getskillhitbox() { return skill->Hitboxlist; }

	// TEMP potion effect
	float speedmultiplier = 1;
	float agilityduration = 0;

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


	Movement_Component* getMovementComponent() { return movement_component; }
	bool iscanJump() { return airJump; }
	void setJump(bool canjump);

	// should consider placing this somewhere projectile related
	void shoot(Game*gamePtr, int x_target, int y_target, TextureManager*textureM);
	void updateProjectiles(float frameTime);
	std::vector<Projectile*>::iterator deleteProjectile(std::vector<Projectile*>::iterator it);

	// melee/hitbox attack prototype
	void punch(/*Game*gamePtr, TextureManager*textureM*/);
	void drawHitboxes();
	void updateHitboxes(float frameTime);
	void deleteHitbox();

};

#endif // _PLAYER_H