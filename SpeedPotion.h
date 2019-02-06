#pragma once
#include "Potion.h"


class SpeedPotion : public Potion
{
public:
	SpeedPotion();
	void apply(Player* player);
	void draw();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	~SpeedPotion();
};

