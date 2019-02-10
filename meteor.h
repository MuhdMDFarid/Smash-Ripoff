
#pragma once
#include "entity.h"
#include "constants.h"

namespace meteorNS
{
	const int WIDTH = 1600;
	const int HEIGHT = 1600;
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI / 4; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
}

class Meteor : public Entity
{
public:
	// constructor
	Meteor();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	~Meteor();
};

