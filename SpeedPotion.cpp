//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "SpeedPotion.h"



SpeedPotion::SpeedPotion()
{
	spriteData.width = PotionNS::WIDTH;
	spriteData.height = PotionNS::HEIGHT;
}

void SpeedPotion::apply(Player * player)
{
	//stuff
	player->speedmultiplier=1.5;
	player->agilityduration = 10;
	//this->setActive(false);
}

void SpeedPotion::draw()
{
	Entity::draw();
}

void SpeedPotion::update(float frametime)
{
	Entity::update(frametime);

}

bool SpeedPotion::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

SpeedPotion::~SpeedPotion()
{
}
