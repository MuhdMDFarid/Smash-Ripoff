#pragma once
#include "Player.h"
#include "entity.h"
#include "constants.h"
#include "heart.h"
#include "Player.h"

namespace PotionNS
{
	const int WIDTH = 30;
	const int HEIGHT = 30;
	const int COLLISION_RADIUS = 30 / 2;
	const float MASS = 50;

}

class Potion :public Entity
{
private:
	Image potion;
	bool isCollided = false;

public:
	Potion();
	float duration;
	virtual void apply(Player* player) = 0;
	virtual void draw() = 0;
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)=0;
	void update(float frameTime) = 0;
	~Potion();
};

