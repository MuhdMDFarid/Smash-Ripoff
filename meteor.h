
#pragma once
#include "entity.h"
#include "constants.h"
#include"Damage_Component.h"

namespace meteorNS
{
	const int WIDTH = 552;
	const int HEIGHT = 552;
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = 0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
}

class Meteor : public Entity
{
private:
	float elapsedtime=0;
	Damage_Component* damageC;
public:
	// constructor
	Meteor();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);

	Damage_Component* getDamageC() { return damageC; }
	~Meteor();
};

