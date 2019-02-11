//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G
#pragma once
#include "Player.h"
#include "entity.h"
#include "constants.h"
#include "heart.h"
#include "Player.h"

namespace PotionNS
{
	const int WIDTH = 67;
	const int HEIGHT = 67;
	const int COLLISION_RADIUS = 67 / 2;
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

