#pragma once
#ifndef _Player_H
#define _Player_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>
#include"ship.h"

#include "Projectile.h"
#include "Movement_Component.h"

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
	std::vector<Projectile*> projectilelist;
	bool canJump;
	
public:
	Projectile *newprojectile;


	Player();

	~Player();

	virtual bool initialize(Game*gamePtr, int width, int height, int ncols, TextureManager*textureM);

	float getSpeed() { return speed; }

	void move(int x_force, int y_force);	// change the forces on the char for movement

	virtual void draw();
	
	void drawProjectiles();

	void update(float frameTime);

	void shoot(Game*gamePtr,int x_target, int y_target,TextureManager*textureM);

	void setCollisionType(entityNS::COLLISION_TYPE coltype);


	// Components stuff
	Movement_Component* getMovementComponent() { return movement_component; }
	bool iscanJump() { return canJump; }
	void setJump(bool canjump);


};

#endif