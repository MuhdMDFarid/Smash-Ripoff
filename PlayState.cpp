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
	game->player.draw();
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

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Vel: %d", (int)game->player.getMovementComponent()->getX_Velocity());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Vel: %d", (int)game->player.getMovementComponent()->getY_Velocity());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 2 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Force: %d", (int)game->player.getMovementComponent()->getX_Force());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 3 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Force: %d", (int)game->player.getMovementComponent()->getY_Force());
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 4 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "projectiles: %d", (int)game->player.jumpcooldown);
		game->buttonFont.printC(gameNS::buffer, GAME_WIDTH / 2, 0 * GAME_HEIGHT / 5);
	//
}

void PlayState::update(float frameTime)
{
	game->player.update(frameTime);
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
	if (!game->player.skill->Hitboxlist.empty())
	{
		for (std::vector<SkillHitbox*>::iterator it = game->player.skill->Hitboxlist.begin(); it != game->player.skill->Hitboxlist.end(); )
		{

			if (game->platformUpList[1].collidesWith(*(*it)->hitbox, collisionVector))
			{
				//game->player.getMovementComponent()->setX_Velocity(game->player.playerface*(*it)->hitbox->getKnockback().x);
				//game->player.getMovementComponent()->setY_Velocity((*it)->hitbox->getKnockback().y);
				//game->player.interrupt(0.5);
				game->player.knockedback((*it)->hitbox);
				break;
			}
			it++;

		}
	}

	// END OF HITBOX COLLISION

	// platform collision
	if (game->player.collidesWith(game->platform1, collisionVector))
	{
		// PROTOTYPE COLLISION Detection

		// collide with top of platform1
		if (game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() >= game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale()
			&& game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() < game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale())
		{
			// player collides from the top of the platform1
			game->player.setY(game->platform1.getCenterY() + game->platform1.getEdge().top * game->platform1.getScale()
				- game->player.getHeight());		// prevents player from moving past the left side of platform1

			if (game->player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
			{	// this is to prevent reseting velocity when player is jumping from the side up wards
				game->player.getMovementComponent()->setY_Velocity(0);
			}

			//player.setJump(true);
			//player.grounded = true;
			if (game->player.airEnum != STATE_GROUNDED)
			{
				game->player.landed();
			}
		}

		else if (game->player.getCenterX() + game->player.getEdge().right * game->player.getScale() >= game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale()
			&& game->player.getCenterX() + game->player.getEdge().left * game->player.getScale() < game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale())
		{
			// player collides from the left side of platform1
			game->player.setX(game->platform1.getCenterX() + game->platform1.getEdge().left * game->platform1.getScale()
				- game->player.getWidth());		// prevents player from moving past the right side of platform1

			if (game->player.getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
			{
				game->player.getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (game->player.getCenterX() + game->player.getEdge().left * game->player.getScale() <= game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale()
			&& game->player.getCenterX() + game->player.getEdge().right * game->player.getScale() > game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale())
		{
			// player collides from right side of platform1
			game->player.setX(game->platform1.getCenterX() + game->platform1.getEdge().right * game->platform1.getScale());		// prevents player from moving past the left side of platform1

			if (game->player.getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
			{
				game->player.getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() <= game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale()
			&& game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() > game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale())
		{
			// player collides from the bottom of the platform1
			game->player.setY(game->platform1.getCenterY() + game->platform1.getEdge().bottom * game->platform1.getScale());

			if (game->player.getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
			{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
				game->player.getMovementComponent()->setY_Velocity(0);
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
	else			// If not colliding with platforms 
	{
		if (game->player.airEnum != STATE_AIRBORNE)
		{
			game->player.fall();
		}

	}
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (game->player.collidesWith(game->platformUpList[i], collisionVector))
		{
			// PROTOTYPE COLLISION Detection

			// collide with top of platformUpList[i]
			if (game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() >= game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
				&& game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() < game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale())
			{

				if (game->player.getMovementComponent()->getY_Velocity() >= 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side up wards
					game->player.getMovementComponent()->setY_Velocity(0);
					// player collides from the top of the platformUpList[i]
					game->player.setY(game->platformUpList[i].getCenterY() + game->platformUpList[i].getEdge().top * game->platformUpList[i].getScale()
						- game->player.getHeight());		// prevents player from moving past the left side of platformUpList[i]
				}

				if (game->player.airEnum != STATE_GROUNDED)
				{
					game->player.landed();
				}
			}
			// end of PROTOTYPE COLLISION DETECTION
		}
	}
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (game->player.collidesWith(game->platformDownList[i], collisionVector))
		{
			// PROTOTYPE COLLISION Detection

			// collide with top of platformDownList[i]
			if (game->player.getCenterY() + game->player.getEdge().bottom * game->player.getScale() >= game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
				&& game->player.getCenterY() + game->player.getEdge().top * game->player.getScale() < game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale())
				//&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
			{
				if (game->player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side Down wards
					game->player.getMovementComponent()->setY_Velocity(-game->YVelocity);
					// player collides from the top of the platformDownList[i]
					game->player.setY(game->platformDownList[i].getCenterY() + game->platformDownList[i].getEdge().top * game->platformDownList[i].getScale()
						- game->player.getHeight());		// prevents player from moving past the left side of platformDownList[i]
				}

				if (game->player.airEnum != STATE_GROUNDED)
				{
					game->player.landed();
				}
			}
			// end of PROTOTYPE COLLISION DETECTION
		}
	}

	if (game->player.collidesWith(game->potion, collisionVector))
	{
		game->potion.apply(&game->player);
	}
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

	game->player.handleInput(input);

	if (input->isKeyDown(E_KEY))
	{
		//player.deleteHitbox();
	}

	
	if (input->getMouseLButton())
	{
		// game->player.shoot(game, input->getMouseX(), input->getMouseY(), &projectileTexture);
	}

	if (input->isKeyDown(VK_SPACE))
	{
		//player.interrupt();
		game->player.punch(/*this, &playerTextures*/);
	}

	/*if (input->isKeyDown(W_KEY) || input->isKeyDown(VK_UP))	//jump
	{
		player.jump();
		//if (player.iscanJump())
		//{
		//	player.getMovementComponent()->setY_Velocity(-250);
		//	player.setJump(false);
		//}
	}
	else*/ 
	//if (input->isKeyDown(S_KEY) || input->isKeyDown(VK_DOWN))	// dive down
	//{
	//	game->player.move(0, game->player.getSpeed() * game->player.speedmultiplier);
	//	//player.getMovementComponent()->setY_Force(100);
	//}
	//else
	//{
	//	game->player.getMovementComponent()->setY_Force(0);
	//}

	//if (input->isKeyDown(A_KEY) || input->isKeyDown(VK_LEFT))	// move left
	//{
	//	//player.move(-player.getSpeed(), 0);
	//	game->player.playerface = -1;
	//	game->player.getMovementComponent()->setX_Force(-game->player.getSpeed() * game->player.speedmultiplier);
	//}
	//else if (input->isKeyDown(D_KEY) || input->isKeyDown(VK_RIGHT))	// move right
	//{
	//	//player.move(player.getSpeed(), 0);
	//	game->player.playerface = 1;
	//	game->player.getMovementComponent()->setX_Force(game->player.getSpeed() * game->player.speedmultiplier);
	//}
	//else { game->player.getMovementComponent()->setX_Force(0); }

	/*//  to make the player loop back on screen
	if (player.getX() > GAME_WIDTH)
	{
		player.setX(-player.getWidth()*player.getScale());
	}
	else if (player.getX() < -player.getWidth()*player.getScale());
	{
		player.setX(GAME_WIDTH);
	}

	if (player.getY() > GAME_HEIGHT)
	{
		player.setY(0 - player.getHeight()*player.getScale());
	}
	else if (player.getY() < -player.getHeight()*player.getScale());
	{
		player.setY(GAME_HEIGHT);
	}*/
}