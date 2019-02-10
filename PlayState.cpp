#include <iostream>
#include "PlayState.h"
#include "PauseState.h"
#include "HunterDeathState.h"
#include "PriestessDeathState.h"

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
	game->platform1.draw();
	game->potion.draw();

	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		game->platformUpList[i].draw();
		game->platformDownList[i].draw();

	}

	for (int i = 0; i < MAX_HEALTH; i++)	// Add Players' Health
	{
		if (game->hunterHealth[i].getActive())	// Checks to see if the heart is active (if it isn't, don't draw it)
		{
			game->hunterHealth[i].draw();
		}

		if (game->priestessHealth[i].getActive())
		{
			game->priestessHealth[i].draw();
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

	// DEBUG
	// Print message
		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "fps %d, Press ESC to pause", (int)game->getfps());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 3, GAME_HEIGHT / 8);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Vel: %d", (int)game->hunter.getMovementComponent()->getX_Velocity());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Vel: %d", (int)game->hunter.getMovementComponent()->getY_Velocity());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 2 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Force: %d", (int)game->hunter.getMovementComponent()->getX_Force());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 3 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Force: %d", (int)game->hunter.getMovementComponent()->getY_Force());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 4 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "projectiles: %d", (int)game->hunter.jumpcooldown);
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 0 * GAME_HEIGHT / 5);
	//
}

void PlayState::update(float frameTime)
{
	game->hunter.update(frameTime);
	game->priestess.update(frameTime);
	game->planet.update(frameTime);
	//platform.update(frameTime);	// should this even have update since platforms dont really move
	game->platform1.update(frameTime);
	game->potion.update(frameTime);

	//hk
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		game->platformUpList[i].updateUp(frameTime);
		game->platformDownList[i].updateDown(frameTime);
	}
	//update every bullet in player ithink
	//
	if(game->getInput()->isKeyDown(VK_SPACE))
		game->hunter.shoot(game, game->hunter.getCenterX() + 10*game->hunter.playerface, game->hunter.getCenterY(), game->hunter.getTextureManager());
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
	/*//if (game->player.collidesWith(game->platform1, collisionVector))
	//{
	//	// PROTOTYPE COLLISION Detection

	//	// collide with top of platform1
	//	if (game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() >= game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale()
	//		&& game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() < game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale())
	//	{
	//		// player collides from the top of the platform1
	//		game->player.setY(game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale()
	//			- game->player.getHeight());		// prevents player from moving past the left side of platform1

	//		if (game->player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
	//		{	// this is to prevent reseting velocity when player is jumping from the side up wards
	//			game->player.getMovementComponent()->setY_Velocity(0);
	//		}

	//		//player.setJump(true);
	//		//player.grounded = true;
	//		if (game->player.airEnum != STATE_GROUNDED)
	//		{
	//			game->player.landed();
	//		}
	//	}

	//	else if (game->player.getCenterX() + game->player.getEdge().right * game->player.getScale() >= game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale()
	//		&& game->player.getCenterX() + game->player.getEdge().left * game->player.getScale() < game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale())
	//	{
	//		// player collides from the left side of platform1
	//		game->player.setX(game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale()
	//			- game->player.getWidth());		// prevents player from moving past the right side of platform1

	//		if (game->player.getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
	//		{
	//			game->player.getMovementComponent()->setX_Velocity(0);
	//		}
	//	}

	//	else if (game->player.getCenterX() + game->player.getEdge().left * game->player.getScale() <= game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale()
	//		&& game->player.getCenterX() + game->player.getEdge().right * game->player.getScale() > game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale())
	//	{
	//		// player collides from right side of platform1
	//		game->player.setX(game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale());		// prevents player from moving past the left side of platform1

	//		if (game->player.getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
	//		{
	//			game->player.getMovementComponent()->setX_Velocity(0);
	//		}
	//	}

	//	else if (game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() <= game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale()
	//		&& game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() > game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale())
	//	{
	//		// player collides from the bottom of the platform1
	//		game->player.setY(game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale());

	//		if (game->player.getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
	//		{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
	//			game->player.getMovementComponent()->setY_Velocity(0);
	//		}
	//	}
	//	// end of PROTOTYPE COLLISION DETECTION


	//	////platform.bounce(collisionVector*-1, player);
	//	//player.bounce(VECTOR2(0,10), platform);
	//	//player.setJump(true);
	//	////player.getMovementComponent()->setY_Force(-player.getMovementComponent()->getY_Velocity());
	//	//player.getMovementComponent()->setY_Velocity(0);



	//	//LOOK AT BOUNCE TO SEE HOW TO STOP VIBRATIONS AND HOW TO HANDLE COLLISIONS
	//	// doesn't test which if statement is for which side of collision
	//	/*if(player.getCenterX() + player.getEdge().right*player.getScale() < platform.getCenterX() + platform.getEdge().left*platform.getScale())
	//	{
	//		// player collides from the left side of platform
	//		player.setX(player.getX() - 100);
	//	}
	//	else if(player.getCenterX() + player.getEdge().left*player.getScale() > platform.getCenterX() + platform.getEdge().right*platform.getScale())
	//	{
	//		// player collides from right side of platform
	//		player.setX(player.getX() + 100);
	//	}
	//	else if(player.getCenterY() + player.getEdge().bottom*player.getScale() < platform.getCenterY() + platform.getEdge().top*platform.getScale())
	//	{
	//		// player collides from the top of the platform
	//		//player.setY(player.getY() - 100);
	//		player.getMovementComponent()->setY_Velocity(0);
	//		player.setJump(true);

	//	}
	//	else if	(player.getCenterY() + player.getEdge().top*player.getScale() > platform.getCenterY() + platform.getEdge().bottom*platform.getScale())
	//	{
	//		// player collides from the bottom of the platform
	//	}
	//}
	//else			// If not colliding with platforms 
	//{
	//	if (game->player.airEnum != STATE_AIRBORNE)
	//	{
	//		game->player.fall();
	//	}

	//}
	//for (int i = 0; i < NO_PLATFORMS; i++)
	//{
	//	if (game->player.collidesWith(game->platformUpList[i], collisionVector))
	//	{
	//		// PROTOTYPE COLLISION Detection

	//		// collide with top of platformUpList[i]
	//		if (game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() >= game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
	//			&& game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() < game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale())
	//		{

	//			if (game->player.getMovementComponent()->getY_Velocity() >= 0)		// if player is moving downwards it sets velocity to 0...
	//			{	// this is to prevent reseting velocity when player is jumping from the side up wards
	//				game->player.getMovementComponent()->setY_Velocity(0);
	//				// player collides from the top of the platformUpList[i]
	//				game->player.setY(game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
	//					- game->player.getHeight());		// prevents player from moving past the left side of platformUpList[i]
	//			}

	//			if (game->player.airEnum != STATE_GROUNDED)
	//			{
	//				game->player.landed();
	//			}
	//		}
	//		// end of PROTOTYPE COLLISION DETECTION
	//	}
	//}
	//for (int i = 0; i < NO_PLATFORMS; i++)
	//{
	//	if (game->player.collidesWith(game->platformDownList[i], collisionVector))
	//	{
	//		// PROTOTYPE COLLISION Detection

	//		// collide with top of platformDownList[i]
	//		if (game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() >= game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
	//			&& game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() < game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale())
	//			//&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
	//		{
	//			if (game->player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
	//			{	// this is to prevent reseting velocity when player is jumping from the side Down wards
	//				game->player.getMovementComponent()->setY_Velocity(-game->YVelocity);
	//				// player collides from the top of the platformDownList[i]
	//				game->player.setY(game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
	//					- game->player.getHeight());		// prevents player from moving past the left side of platformDownList[i]
	//			}

	//			if (game->player.airEnum != STATE_GROUNDED)
	//			{
	//				game->player.landed();
	//			}
	//		}
	//		// end of PROTOTYPE COLLISION DETECTION
	//	}
	//}
*/

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

		if (game->hunterHP > 0)
		{
			game->hunterHealth[game->hunterHP].setActive(false);
			game->hunterHP--;
		}

		else
		{
			game->hunterDeath = true;
		}
	}

	// Priestess
	if (input->isKeyDown(P_KEY))
	{
		input->keyUp(P_KEY);

		if (game->priestessHP > 0)
		{
			game->priestessHealth[game->priestessHP].setActive(false);
			game->priestessHP--;
		}

		else
		{
			game->priestessDeath = true;
		}
	}

	game->hunter.handleInput(input);
	game->priestess.handleInput(input);
	//if (input->isKeyDown(E_KEY))
	//{
	//	//player.deleteHitbox();
	//}

	
	if (input->getMouseLButton())
	{
		// game->player.shoot(game, input->getMouseX(), input->getMouseY(), &projectileTexture);
	}
}
void PlayState::playercollision(Player* p)
{
	VECTOR2 collisionVector;
	bool platformcollided = false;

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
			//player.setJump(true);
			//player.grounded = true;
			//if (platformcollided) 
			//{
			//	if (p->airEnum != STATE_GROUNDED)
			//	{
			//		p->landed();
			//	}
			//}
			//else
			//{
			//	if (p->airEnum != STATE_AIRBORNE)
			//	{
			//		// WHY DOES player keep running fall() even when on platform
			//		p->fall();
			//	}
			//}
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
		// end of PROTOTYPE COLLISION DETECTION


		////platform.bounce(collisionVector*-1, player);
		//player.bounce(VECTOR2(0,10), platform);
		//player.setJump(true);
		////player.getMovementComponent()->setY_Force(-player.getMovementComponent()->getY_Velocity());
		//player.getMovementComponent()->setY_Velocity(0);



		//LOOK AT BOUNCE TO SEE HOW TO STOP VIBRATIONS AND HOW TO HANDLE COLLISIONS
		// doesn't test which if statement is for which side of collision
		/*if(player.getCenterX() + player.getEdge().right*player.getScale() < platform.getCenterX() + platform.getEdge().left*platform.getScale())
		{
			// player collides from the left side of platform
			player.setX(player.getX() - 100);
		}
		else if(player.getCenterX() + player.getEdge().left*player.getScale() > platform.getCenterX() + platform.getEdge().right*platform.getScale())
		{
			// player collides from right side of platform
			player.setX(player.getX() + 100);
		}
		else if(player.getCenterY() + player.getEdge().bottom*player.getScale() < platform.getCenterY() + platform.getEdge().top*platform.getScale())
		{
			// player collides from the top of the platform
			//player.setY(player.getY() - 100);
			player.getMovementComponent()->setY_Velocity(0);
			player.setJump(true);

		}
		else if	(player.getCenterY() + player.getEdge().top*player.getScale() > platform.getCenterY() + platform.getEdge().bottom*platform.getScale())
		{
			// player collides from the bottom of the platform
		}*/
	}
	//else			// If not colliding with platforms 
	//{


	//}
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
					p->getMovementComponent()->setY_Velocity(0);
					// player collides from the top of the platformUpList[i]
					p->setY(game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
						- p->getHeight());		// prevents player from moving past the left side of platformUpList[i]
				}
				platformcollided = true;

				//if (p->airEnum != STATE_GROUNDED)
				//{
				//	p->landed();
				//}
			}
			// end of PROTOTYPE COLLISION DETECTION
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
				if (p->getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side Down wards
					p->getMovementComponent()->setY_Velocity(-game->YVelocity);
					// player collides from the top of the platformDownList[i]
					p->setY(game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
						- p->getHeight());		// prevents player from moving past the left side of platformDownList[i]
				}
				platformcollided = true;
/*
				if (p->airEnum != STATE_GROUNDED)
				{
					p->landed();
				}*/
			}
			// end of PROTOTYPE COLLISION DETECTION
		}
	}
	if (p->collidesWith(game->potion, collisionVector))
	{
		game->potion.apply(p);
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
}