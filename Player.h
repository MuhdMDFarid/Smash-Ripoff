//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _Player_H
#define _Player_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>
//#include"ship.h"

//#include "Controlled_Projectile_Hitbox.h"
#include "Projectile_Hitbox.h"
#include "Movement_Component.h"
//#include "Hitbox.h"
#include "PlayerInput_Component.h"
#include "heart.h"

class Hitbox;

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


namespace PlayerNS
{
	//int WIDTH = 64;
	//int HEIGHT = 64;
	const int TEXTURE_COLS = 4;
	const float PLAYER_MOVE_DELAY = 0.2f;

	const float JUMP_CD = 0.5f;
	const int JUMP_VELOCITY = 500;

	const float BASE_KNOCKBACK_MULTIPLIER = 15;

	//// Player 1 (Bounty Hunter)
	//const UCHAR P1_UP = W_KEY;
	//const UCHAR P1_DOWN = S_KEY;
	//const UCHAR P1_LEFT = A_KEY;
	//const UCHAR P1_RIGHT = D_KEY;
	//const UCHAR P1_ATTACK = R_KEY;
	//const UCHAR P1_SPECIAL = T_KEY;

	//// Player 2 (Priestess)
	//const UCHAR P2_UP = UP_KEY;
	//const UCHAR P2_DOWN = DOWN_KEY;
	//const UCHAR P2_LEFT = LEFT_KEY;
	//const UCHAR P2_RIGHT = RIGHT_KEY;
	//const UCHAR P2_ATTACK = PERIOD_KEY;
	//const UCHAR P2_SPECIAL = COMMA_KEY;
	//

	// Player 1 Frames
	const int P1_IDLE_START = 0;
	const int P1_IDLE_END = 3;

	const int P1_MOVE_START = 4;
	const int P1_MOVE_END = 7;

	const int P1_ATTACK_START = 8;
	const int P1_ATTACK_END = 11;

	const int P1_AIRBORNE_START = 12;
	const int P1_AIRBORNE_END = 15;

	const int P1_STAGGERED_START = 16;
	const int P1_STAGGERED_END = 19;
	
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
	PlayerInput_Component* pk_bind;				// Player Key Bindings

	float kbMultiplier;

public:
	//bool grounded;		// replaced to a state in future
	void landed();
	void fall();
	void jump();
	void interrupt(float stunduration = 1);		// for when player gets hit *no knock back involved
	void knockback(float xV, float yV);	// when player collides with hitbox
	void hitted(Damage_Component* damageC);
	State airEnum;
	PlayerState* airborne;
	State actionEnum;
	PlayerState* action;
	float jumpcooldown;
	bool airJump;
	bool canjump;

	int playerface;

	// get the PlayerInput Component
	PlayerInput_Component* getPK() { return pk_bind; }
	void setPK(PlayerInput_Component* pk) { 
		delete pk_bind;
		pk_bind = pk;
	}

	// GHETTO
	Game* game = nullptr;
	TextureManager* getTextureManager() { return textureManager; }

	void handleInput(Input* input);


	Projectile_Hitbox *newprojectile;		// not sure if this should be done
	std::vector<Projectile_Hitbox*> projectilelist;

	// hitbox_attack components stuff
	std::vector<Hitbox*> hitboxlist;		// this should be placed in a hitbox_attack component
	Hitbox *newhitbox;		// this should be placed in a hitbox_attack
	
	Skill* skill;
	//Skill* normals;
	//Skill* specials;
	//std::vector<SkillHitbox*> getskillhitbox() { return skill->Hitboxlist; }

	// Speed potion effect
	float speedmultiplier = 1; // set base speed
	float agilityduration = 0; // set inactive

	// TEMP HP potion effect
	static const int MAX_HEALTH = 3;
	// Players' Health
	Heart Health[MAX_HEALTH];
	// List starts from 0
	//int hunterHP = 2;
	//int priestessHP = 2;

	int HP = 2;

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
	void death();

	//void setCollisionType(entityNS::COLLISION_TYPE coltype);


	Movement_Component* getMovementComponent() { return movement_component; }
	bool iscanJump() { return airJump; }
	void setJump(bool canjump);

	// should consider placing this somewhere projectile related
	void shoot(Game*gamePtr, int x_target, int y_target, TextureManager*textureM);
	//void updateProjectiles(float frameTime);
	std::vector<Projectile_Hitbox*>::iterator deleteProjectile(std::vector<Projectile_Hitbox*>::iterator it);

	// hitbox attack
	void drawHitboxes();
	void updateHitboxes(float frameTime);
	void deleteHitbox();

	// attack
	void normalS(/*Game*gamePtr, TextureManager*textureM*/);
	void specialS();


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

#endif // _PLAYER_H