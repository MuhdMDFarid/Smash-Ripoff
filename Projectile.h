#pragma once
#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "entity.h"
#include "constants.h"
#include "Movement_Component.h"

class Projectile : public Entity
{
private:
	float lifetime=10.0f;
	float projectileSpeed=10.0f;
	float damage;
	Movement_Component * movement_component;	// Movement component to control the forces of movement

public:
	Projectile();
	~Projectile();
	
	virtual void draw();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);

	void setForce(int x_force, int y_force);

	void update(float frameTime);

	void remove();
	//void damage(WEAPON weapon);

};

#endif