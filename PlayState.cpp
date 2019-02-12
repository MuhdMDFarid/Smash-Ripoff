//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include <iostream>
#include "PlayState.h"
#include "PauseState.h"
#include "HunterDeathState.h"
#include "PriestessDeathState.h"

#include "Player.h"

#include "Potion.h"
#include "SpeedPotion.h"
#include "HealthPotion.h"
#include "Landmine.h"
#include "meteor.h"

PlayState::PlayState(SmashRipoff* game)
{
	// Gets the instance of the game as a pointer
	this->game = game;
}

void PlayState::pauseGame()
{
	// Transitions from "PlayState" to "PauseState"
	game->pushState(new PauseState(game));
}

void PlayState::draw()
{
	game->nebula.draw();
	game->planet.draw();
	game->hunter.draw();
	game->priestess.draw();
	game->platform.draw();
	game->platform1.draw();
	game->healthpotion.draw();
	game->speedpotion.draw();
	game->landmine.draw();
	game->meteor.draw();

	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		game->platformUpList[i].draw();
		game->platformDownList[i].draw();

	}

	for (int i = 0; i < MAX_HEALTH; i++)	// Add Players' Health
	{
		if (game->hunter.Health[i].getActive())	// Checks to see if the heart is active (if it isn't, don't draw it)
		{
			game->hunter.Health[i].draw();
		}

		if (game->priestess.Health[i].getActive())
		{
			game->priestess.Health[i].draw();
		}
	}

	if (game->hunterDeath)
	{
		game->pushState(new HunterDeathState(game));
		game->hunterDeath = false;
	}

	if (game->priestessDeath)
	{
		game->pushState(new PriestessDeathState(game));
		game->priestessDeath = false;
	}
}

void PlayState::update(float frameTime)
{
	game->hunter.update(frameTime);
	game->priestess.update(frameTime);
	game->planet.update(frameTime);
	game->platform.update(frameTime);
	game->platform1.update(frameTime);
	game->speedpotion.update(frameTime);
	game->healthpotion.update(frameTime);
	game->meteor.update(frameTime);

	if (game->hunter.HP < 0)
	{
		game->hunterDeath = true;
	}

	if (game->priestess.HP < 0)
	{
		game->priestessDeath = true;
	}

	//hk
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		game->platformUpList[i].updateUpDown(frameTime);
		game->platformDownList[i].updateUpDown(frameTime);
	}
	//update every bullet in player ithink
	//
	//if(game->getInput()->isKeyDown(VK_SPACE))
	//	game->hunter.shoot(game, game->hunter.getCenterX() + 10*game->hunter.playerface, game->hunter.getCenterY(), game->hunter.getTextureManager());
	//if (player.airEnum != STATE_AIRBORNE)
	//{
	//	player.fall();
	//}
}

void PlayState::ai()
{

}

void PlayState::collisions()
{
	VECTOR2 collisionVector;

	// HITBOX collision
	if (!game->hunter.hitboxlist.empty())
	{
		for (std::vector<Hitbox*>::iterator it = game->hunter.hitboxlist.begin(); it != game->hunter.hitboxlist.end(); )
		{
			if (game->priestess.collidesWith(*(*it), collisionVector))
			{
				//game->player.getMovementComponent()->setX_Velocity(game->player.playerface*(*it)->hitbox->getKnockback().x);
				//game->player.getMovementComponent()->setY_Velocity((*it)->hitbox->getKnockback().y);
				//game->player.interrupt(0.5);
				game->priestess.hitted((*it)->getDamageC());
				(*it)->collided();
				break;
			}
			it++;
		}
	}

	if (!game->priestess.hitboxlist.empty())
	{
		for (std::vector<Hitbox*>::iterator it = game->priestess.hitboxlist.begin(); it != game->priestess.hitboxlist.end(); )
		{

			if (game->hunter.collidesWith(*(*it), collisionVector))
			{
				//game->player.getMovementComponent()->setX_Velocity(game->player.playerface*(*it)->hitbox->getKnockback().x);
				//game->player.getMovementComponent()->setY_Velocity((*it)->hitbox->getKnockback().y);
				//game->player.interrupt(0.5);
				game->hunter.hitted((*it)->getDamageC());
				(*it)->collided();
				break;
			}
			it++;

		}
	}

	// END OF HITBOX COLLISION

	// platform collision
	playercollision(&game->hunter);
	playercollision(&game->priestess);

	//if (game->player.collidesWith(game->potion, collisionVector))
	//{
	//	game->potion.apply(&game->player);
	//}
}

void PlayState::handleInput(Input* input)
{
	// Keyboard
	// Pauses the game
	if (input->isKeyDown(ESC_KEY))
	{
		// Ensures that the key doesn't register more than once
		input->keyUp(ESC_KEY);
		pauseGame();
	}

	// --Hearts-- (replace in Collision, Muhamiddo)
	// Hunter
	if (input->isKeyDown(O_KEY))
	{
		input->keyUp(O_KEY);

		if (game->hunter.HP > 0)
		{
			game->hunter.Health[game->hunter.HP].setActive(false);
			game->hunter.HP--;
		}
	}
	if (input->isKeyDown(O_KEY))
	{
		input->keyUp(O_KEY);

		if (game->priestess.HP > 0)
		{
			game->priestess.Health[game->priestess.HP].setActive(false);
			game->priestess.HP--;
		}
	}
	// Priestess
	//if (input->isKeyDown(P_KEY))
	//{
	//	input->keyUp(P_KEY);

	//	if (game->hunter.HP > 0)
	//	{
	//		game->priestessHealth[game->priestessHP].setActive(false);
	//		game->priestessHP--;
	//	}

	//	else
	//	{
	//		game->priestessDeath = true;
	//	}
	//}

	game->hunter.handleInput(input);
	game->priestess.handleInput(input);
	//if (input->isKeyDown(E_KEY))
	//{
	//	//player.deleteHitbox();
	//}
}
void PlayState::playercollision(Player* p)
{
	VECTOR2 collisionVector;
	bool platformcollided = false;

	if (p->collideRotatedBox(game->platform, collisionVector))
	{
		// PROTOTYPE COLLISION Detection
		if (p->getX() > game->platform.getCenterX()) // check if p-> is at the right side of the game->platform
		{
			if (p->getY() > game->platform.getCenterY()) // check if p-> is at the bottom right side of the game->platform
			{
				p->setX(p->getX() +2/*+ game->platform.getCenterX()*/); // move away from the center of game->platform
				p->setY(p->getY() -2/*- game->platform.getCenterY()*/);
			}
			else if (p->getY() < game->platform.getCenterY()) // check if the p-> is at the top right side of the game->platform
			{
				p->setX(p->getX() -2/*- game->platform.getCenterX()*/); // move towards the center of the game->platform since the game->platform will be like /
				p->setY(p->getY() +2/*+ game->platform.getCenterY()*/);
				p->setY(p->getY() +2/*+ game->platform.getCenterY()*/);
			}
		}
		else if (p->getX() < game->platform.getCenterX()) // check if p-> is the left side of the game->platform
		{
			if (p->getY() > game->platform.getCenterY())  // check if the p-> is at the bottom left side of the game->platform
			{
				p->setX(p->getX() + 2/*+ game->platform.getCenterX()*/); // move towards the right
				p->setY(p->getY() + 2/*+ game->platform.getCenterY()*/);
			}
			else if (p->getY() < game->platform.getCenterY()) // check if the p-> is at the top left side of the game->platform
			{
				p->setX(p->getX() -2/*- game->platform.getCenterX()*/); // move towards the  left
				p->setY(p->getY() -2/*- game->platform.getCenterY()*/);
			}
		}

		if (p->airEnum != STATE_GROUNDED)
		{
			p->landed();
		}
		// end of PROTOTYPE COLLISION DETECTION
		else if (p->airEnum != STATE_AIRBORNE)		// If not colliding with game->platform1
		{
			p->fall();
		}
	}

	if (p->collidesWith(game->platform1, collisionVector))
	{
		// PROTOTYPE COLLISION Detection

		// collide with top of platform1
		if (p->getCenterY() + p->getEdge().bottom * p->getScale() >= game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale()
			&& p->getCenterY() + p->getEdge().top * p->getScale() < game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale())
		{
			// player collides from the top of the platform1
			p->setY(game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale()
				- p->getHeight());		// prevents player from moving past the left side of platform1

			if (p->getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
			{	// this is to prevent reseting velocity when player is jumping from the side up wards
				p->getMovementComponent()->setY_Velocity(0);
			}
			platformcollided = true;
		}

		else if (p->getCenterX() + p->getEdge().right * p->getScale() >= game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale()
			&& p->getCenterX() + p->getEdge().left * p->getScale() < game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale())
		{
			// player collides from the left side of platform1
			p->setX(game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale()
				- p->getWidth());		// prevents player from moving past the right side of platform1

			if (p->getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
			{
				p->getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (p->getCenterX() + p->getEdge().left * p->getScale() <= game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale()
			&& p->getCenterX() + p->getEdge().right * p->getScale() > game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale())
		{
			// player collides from right side of platform1
			p->setX(game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale());		// prevents player from moving past the left side of platform1

			if (p->getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
			{
				p->getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (p->getCenterY() + p->getEdge().top * p->getScale() <= game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale()
			&& p->getCenterY() + p->getEdge().bottom * p->getScale() > game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale())
		{
			// player collides from the bottom of the platform1
			p->setY(game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale());

			if (p->getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
			{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
				p->getMovementComponent()->setY_Velocity(0);
			}
		}
	}

	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (p->collidesWith(game->platformUpList[i], collisionVector))
		{
			// PROTOTYPE COLLISION Detection

			// collide with top of platformUpList[i]
			if (p->getCenterY() + p->getEdge().bottom * p->getScale() >= game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
				&& p->getCenterY() + p->getEdge().top * p->getScale() < game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale())
			{

				if (p->getMovementComponent()->getY_Velocity() >= 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side up wards
					p->getMovementComponent()->setY_Velocity(-game->YVelocity);
					// player collides from the top of the platformUpList[i]
					p->setY(game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
						- p->getHeight());		// prevents player from moving past the left side of platformUpList[i]
				}
				platformcollided = true;
			}
			// end of PROTOTYPE COLLISION DETECTION
			/*else if (p->getCenterX() + p->getEdge().right * p->getScale() >= game->platformUpList[i].getCenterX() + game->platformUpList[i].getEdge().left * game->platformUpList[i].getScale()
				&& p->getCenterX() + p->getEdge().left * p->getScale() < game->platformUpList[i].getCenterX() + game->platformUpList[i].getEdge().left * game->platformUpList[i].getScale())
			{
				// player collides from the left side of platform1
				p->setX(game->platformUpList[i].getCenterX() + game->platformUpList[i].getEdge().left * game->platformUpList[i].getScale()
					- p->getWidth());		// prevents player from moving past the right side of platform1

				if (p->getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
				{
					p->getMovementComponent()->setX_Velocity(0);
				}
			}

			else if (p->getCenterX() + p->getEdge().left * p->getScale() <= game->platformUpList[i].getCenterX() + game->platformUpList[i].getEdge().right * game->platformUpList[i].getScale()
				&& p->getCenterX() + p->getEdge().right * p->getScale() > game->platformUpList[i].getCenterX() + game->platformUpList[i].getEdge().right * game->platformUpList[i].getScale())
			{
				// player collides from right side of platform1
				p->setX(game->platformUpList[i].getCenterX() + game->platformUpList[i].getEdge().right * game->platformUpList[i].getScale());		// prevents player from moving past the left side of platform1

				if (p->getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
				{
					p->getMovementComponent()->setX_Velocity(0);
				}
			}

			else if (p->getCenterY() + p->getEdge().top * p->getScale() <= game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().bottom * game->platformUpList[i].getScale()
				&& p->getCenterY() + p->getEdge().bottom * p->getScale() > game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().bottom * game->platformUpList[i].getScale())
			{
				// player collides from the bottom of the platform1
				p->setY(game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().bottom * game->platformUpList[i].getScale());

				if (p->getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
				{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
					p->getMovementComponent()->setY_Velocity(0);
				}
			}*/
		}
	}
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (p->collidesWith(game->platformDownList[i], collisionVector))
		{
			// PROTOTYPE COLLISION Detection

			// collide with top of platformDownList[i]
			if (p->getCenterY() + p->getEdge().bottom * p->getScale() >= game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
				&& p->getCenterY() + p->getEdge().top * p->getScale() < game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale())
				//&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
			{
				if (p->getMovementComponent()->getY_Velocity() >= 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side Down wards
					p->getMovementComponent()->setY_Velocity(-game->YVelocity);
					// player collides from the top of the platformDownList[i]
					p->setY(game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
						- p->getHeight());		// prevents player from moving past the left side of platformDownList[i]
				}
				platformcollided = true;
			}
			// end of PROTOTYPE COLLISION DETECTION
			/*else if (p->getCenterX() + p->getEdge().right * p->getScale() >= game->platformDownList[i].getCenterX() + game->platformDownList[i].getEdge().left * game->platformDownList[i].getScale()
				&& p->getCenterX() + p->getEdge().left * p->getScale() < game->platformDownList[i].getCenterX() + game->platformDownList[i].getEdge().left * game->platformDownList[i].getScale())
			{
				// player collides from the left side of platform1
				p->setX(game->platformDownList[i].getCenterX() + game->platformDownList[i].getEdge().left * game->platformDownList[i].getScale()
					- p->getWidth());		// prevents player from moving past the right side of platform1

				if (p->getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
				{
					p->getMovementComponent()->setX_Velocity(0);
				}
			}

			else if (p->getCenterX() + p->getEdge().left * p->getScale() <= game->platformDownList[i].getCenterX() + game->platformDownList[i].getEdge().right * game->platformDownList[i].getScale()
				&& p->getCenterX() + p->getEdge().right * p->getScale() > game->platformDownList[i].getCenterX() + game->platformDownList[i].getEdge().right * game->platformDownList[i].getScale())
			{
				// player collides from right side of platform1
				p->setX(game->platformDownList[i].getCenterX() + game->platformDownList[i].getEdge().right * game->platformDownList[i].getScale());		// prevents player from moving past the left side of platform1

				if (p->getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
				{
					p->getMovementComponent()->setX_Velocity(0);
				}
			}

			else if (p->getCenterY() + p->getEdge().top * p->getScale() <= game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().bottom * game->platformDownList[i].getScale()
				&& p->getCenterY() + p->getEdge().bottom * p->getScale() > game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().bottom * game->platformDownList[i].getScale())
			{
				// player collides from the bottom of the platform1
				p->setY(game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().bottom * game->platformDownList[i].getScale());

				if (p->getMovementComponent()->getY_Velocity() < 0)		// if player is moving Downwards it sets velocity to 0...
				{	// this is to prevent player from keeping Downwards velocity when hitting the bottom of plat
					p->getMovementComponent()->setY_Velocity(0);
				}
			}*/
		}
	}
	// ben speed potion apply
	if (p->collidesWith(game->speedpotion, collisionVector))
	{
		game->speedpotion.apply(p);
	}

	if (p->collidesWith(game->healthpotion, collisionVector))
	{
		game->healthpotion.apply(p);
	}

	if (platformcollided)
	{
		if (p->airEnum != STATE_GROUNDED)
		{
			p->landed();
		}
	}
	else
	{
		if (p->airEnum != STATE_AIRBORNE)
		{
			// WHY DOES player keep running fall() even when on platform
			p->fall();
		}
	}

	//landmine collision
	if (p->collidesWith(game->landmine, collisionVector))
	{
		p->getMovementComponent()->setY_Velocity(-p->getMovementComponent()->getY_Velocity() * 2);
		p->getMovementComponent()->setX_Velocity(-p->getMovementComponent()->getX_Velocity() * 2);
		p->hitted(game->landmine.getDamageC());
		game->landmine.setScale(0);
		game->landmine.setActive(false);
	}

	// meteor collision
	if (p->collidesWith(game->meteor, collisionVector))
	{
		p->getMovementComponent()->setY_Velocity(-p->getMovementComponent()->getY_Velocity() * 2);
		p->getMovementComponent()->setX_Velocity(-p->getMovementComponent()->getX_Velocity() * 2);
		p->hitted(game->meteor.getDamageC());
		//game->meteor.setScale(0);
		//game->meteor.setActive(false);
	}
}