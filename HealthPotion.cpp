#include "HealthPotion.h"


HealthPotion::HealthPotion()
{
	spriteData.width = PotionNS::WIDTH;
	spriteData.height = PotionNS::HEIGHT;
}

void HealthPotion::apply(Player * player)
{
	//stuff
	//player.addHeart;
	if (player->hunterHP >= 0)
	{
		if (player->hunterHP == 2)
		{
			this->setScale(0);
			this->setActive(false);
		}
		else 
		{
			player->hunterHP++;
			player->hunterHealth[player->hunterHP].setActive(true);
			this->setScale(0);
			this->setActive(false);
		}
	}
	
	if (player->priestessHP >= 0)
	{
		if (player->priestessHP == 2)
		{
			this->setScale(0);
			this->setActive(false);
		}
		else 
		{
			player->priestessHP++;
			player->priestessHealth[player->priestessHP].setActive(true);
			this->setScale(0);
			this->setActive(false);
		}
		
	}
}

void HealthPotion::draw()
{
	Entity::draw();
}

void HealthPotion::update(float frametime)
{
	Entity::update(frametime);

}

bool HealthPotion::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

HealthPotion::~HealthPotion()
{
}
