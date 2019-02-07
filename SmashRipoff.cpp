#include "SmashRipoff.h"

//=============================================================================
// Constructor
//=============================================================================
SmashRipoff::SmashRipoff()
{
}

//=============================================================================
// Destructor
//=============================================================================
SmashRipoff::~SmashRipoff()
{
	// Call onLostDevice() for every graphics item
    releaseAll();
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void SmashRipoff::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // nebula texture
    if (!nebulaTexture.initialize(graphics,STAGE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTexture.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	nebula.setScale(5);

    // planet
    if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// main game textures
	if (!playerTexture.initialize(graphics, PLAYER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));

	if (!player.initialize(this, 32, 32,PlayerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));	


	// projectile texture
	if (!projectileTexture.initialize(graphics, PROJECTILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile texture"));

	/// platform texture
	if (!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));



	if (!platform1.initialize(this, GAME_WIDTH, 32, 1, &platformTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	platform1.setX(0);
	platform1.setY(GAME_HEIGHT-platform1.getHeight());

	// Hearts
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		if (!hunterHealth[i].initialize(this, heartNS::WIDTH, heartNS::HEIGHT, 0, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hearts"));
		// Makes the image bigger
		hunterHealth[i].setScale(2);
		// Sets it to the left of the screen (player 1)
		hunterHealth[i].setX(heartNS::WIDTH * i);			
		// Sets it to the bottom of the screen (ensures that it doesn't go below the screen)
		hunterHealth[i].setY(GAME_HEIGHT - (heartNS::HEIGHT * hunterHealth[i].getScale()));
	}

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		if (!priestessHealth[i].initialize(this, heartNS::WIDTH, heartNS::HEIGHT, 0, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hearts"));
		// Makes the image bigger
		priestessHealth[i].setScale(2);
		// Sets it to the right of the screen (player 2)
		priestessHealth[i].setX(GAME_WIDTH - ((heartNS::WIDTH * (i + 1)) + heartNS::WIDTH));
		// Sets it to the bottom of the screen (ensures that it doesn't go below the screen)
		priestessHealth[i].setY(GAME_HEIGHT - (heartNS::HEIGHT * priestessHealth[i].getScale()));
	}

	//hk
	// for moving platforms
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (!platformUpList[i].initialize(this, 160, 32, 1, &platformTexture))	// 1 since texture has only one image
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
		platformUpList[i].setDegrees(0);
		platformUpList[i].setX(3 * GAME_WIDTH / 5);
		platformUpList[i].setY(GAME_HEIGHT / 2 * (NO_PLATFORMS - i));
		platformUpList[i].setVelocity(VECTOR2(0, -TILE_SIZE * 4));

		if (!platformDownList[i].initialize(this, 160, 32, 1, &platformTexture))	// 1 since texture has only one image
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
		platformDownList[i].setDegrees(0);
		platformDownList[i].setX(GAME_WIDTH / 5);
		platformDownList[i].setY(GAME_HEIGHT / 2 * (NO_PLATFORMS - i));
		platformDownList[i].setVelocity(VECTOR2(0, TILE_SIZE * 4));
	}

	///

	// TEMP POTION texture
	if (!potionTexture.initialize(graphics, SPEEDPOTION_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SPD POT textures"));

	if (!potion.initialize(this, 113, 113, 1, &potionTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing potion"));
	potion.setScale(0.5);
	potion.setX(GAME_WIDTH/2 - potion.getScale()*potion.getWidth());
	potion.setY(GAME_HEIGHT/2 - potion.getScale()*potion.getWidth());


    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SmashRipoff::update()
{
	player.update(frameTime);
	// --Hearts-- (replace in Collision, Muhamiddo)
	// Hunter
	if (input->isKeyDown(O_KEY))
	{
		input->keyUp(O_KEY);

		if (hunterHP > 0)
		{
			hunterHealth[hunterHP].setActive(false);
			hunterHP--;
		}

		else
		{
			hunterDeath = true;
		}
	}

	// Priestess
	if (input->isKeyDown(P_KEY))
	{
		input->keyUp(P_KEY);

		if (priestessHP > 0)
		{
			priestessHealth[priestessHP].setActive(false);
			priestessHP--;
		}

		else
		{
			priestessDeath = true;
		}
	}

	//player.fall();
	//if (platform.getY() <= -platform.getHeight())
	//	platform.setY(GAME_HEIGHT);
	//platform.setY(platform.getY() - TILE_SIZE*4*frameTime);

	if (input->isKeyDown(E_KEY))
	{
		//player.deleteHitbox();
	}

	if (input->getMouseLButton())
	{
		player.shoot(this, input->getMouseX(), input->getMouseY(),&projectileTexture);
	}



	if (input->isKeyDown(VK_SPACE))
	{
		//player.interrupt();
		player.punch(/*this, &playerTextures*/);
	}

	player.handleInput(input);
	/*if (input->isKeyDown(W_KEY) || input->isKeyDown(VK_UP))	//jump
	{
		player.jump();
		//if (player.iscanJump())
		//{
		//	player.getMovementComponent()->setY_Velocity(-250);
		//	player.setJump(false);
		//}
	}
	else*/ if (input->isKeyDown(S_KEY)|| input->isKeyDown(VK_DOWN))	// dive down
	{
		player.move(0, player.getSpeed()*player.speedmultiplier);
		//player.getMovementComponent()->setY_Force(100);
	}
	else
	{
		player.getMovementComponent()->setY_Force(0);
	}

	if (input->isKeyDown(A_KEY) || input->isKeyDown(VK_LEFT))	// move left
	{
		//player.move(-player.getSpeed(), 0);
		player.playerface = -1;
		player.getMovementComponent()->setX_Force(-player.getSpeed()*player.speedmultiplier);
	}
	else if (input->isKeyDown(D_KEY) || input->isKeyDown(VK_RIGHT))	// move right
	{
		//player.move(player.getSpeed(), 0);
		player.playerface = 1;
		player.getMovementComponent()->setX_Force(player.getSpeed()*player.speedmultiplier);
	}
	else { player.getMovementComponent()->setX_Force(0); }
	
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

	planet.update(frameTime);

	//platform.update(frameTime);	// should this even have update since platforms dont really move
	platform1.update(frameTime);

	potion.update(frameTime);

	//hk
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		platformUpList[i].updateUp(frameTime);
		platformDownList[i].updateDown(frameTime);
	}
	//update every bullet in player ithink
	//
	//if (player.airEnum != STATE_AIRBORNE)
	//{
	//	player.fall();
	//}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void SmashRipoff::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void SmashRipoff::collisions()
{
	VECTOR2 collisionVector;
	// platform collision
	if(player.collidesWith(platform1,collisionVector))
	{
		// PROTOTYPE COLLISION Detection

		// collide with top of platform1
		if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platform1.getCenterY() + platform1.getEdge().top*platform1.getScale()
			&& player.getCenterY() + player.getEdge().top*player.getScale() < platform1.getCenterY() + platform1.getEdge().top*platform1.getScale())
		{
			// player collides from the top of the platform1
			player.setY(platform1.getCenterY() + platform1.getEdge().top*platform1.getScale()
				- player.getHeight());		// prevents player from moving past the left side of platform1

			if (player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
			{	// this is to prevent reseting velocity when player is jumping from the side up wards
				player.getMovementComponent()->setY_Velocity(0);
			}

			//player.setJump(true);
			//player.grounded = true;
			if (player.airEnum != STATE_GROUNDED)
			{
				player.landed();
			}
		}

		else if (player.getCenterX() + player.getEdge().right*player.getScale() >= platform1.getCenterX() + platform1.getEdge().left*platform1.getScale()
			&& player.getCenterX() + player.getEdge().left*player.getScale() < platform1.getCenterX() + platform1.getEdge().left*platform1.getScale())
		{
			// player collides from the left side of platform1
			player.setX(platform1.getCenterX() + platform1.getEdge().left*platform1.getScale()
				- player.getWidth());		// prevents player from moving past the right side of platform1

			if (player.getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
			{
				player.getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (player.getCenterX() + player.getEdge().left*player.getScale() <= platform1.getCenterX() + platform1.getEdge().right*platform1.getScale()
			&& player.getCenterX() + player.getEdge().right*player.getScale() > platform1.getCenterX() + platform1.getEdge().right*platform1.getScale())
		{
			// player collides from right side of platform1
			player.setX(platform1.getCenterX() + platform1.getEdge().right*platform1.getScale());		// prevents player from moving past the left side of platform1

			if (player.getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
			{
				player.getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (player.getCenterY() + player.getEdge().top*player.getScale() <= platform1.getCenterY() + platform1.getEdge().bottom*platform1.getScale()
			&& player.getCenterY() + player.getEdge().bottom*player.getScale() > platform1.getCenterY() + platform1.getEdge().bottom*platform1.getScale())
		{
			// player collides from the bottom of the platform1
			player.setY(platform1.getCenterY() + platform1.getEdge().bottom*platform1.getScale());

			if (player.getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
			{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
				player.getMovementComponent()->setY_Velocity(0);
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
		if (player.airEnum != STATE_AIRBORNE)
		{
			player.fall();
		}

	}
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (player.collidesWith(platformUpList[i], collisionVector))
		{
			// PROTOTYPE COLLISION Detection

			// collide with top of platformUpList[i]
			if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platformUpList[i].getCenterY() + platformUpList[i].getEdge().top*platformUpList[i].getScale()
				&& player.getCenterY() + player.getEdge().top*player.getScale() < platformUpList[i].getCenterY() + platformUpList[i].getEdge().top*platformUpList[i].getScale())
			{

				if (player.getMovementComponent()->getY_Velocity() >= 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side up wards
					player.getMovementComponent()->setY_Velocity(0);
					// player collides from the top of the platformUpList[i]
					player.setY(platformUpList[i].getCenterY() + platformUpList[i].getEdge().top*platformUpList[i].getScale()
						- player.getHeight());		// prevents player from moving past the left side of platformUpList[i]
				}

				if (player.airEnum != STATE_GROUNDED)
				{
					player.landed();
				}
			}
			// end of PROTOTYPE COLLISION DETECTION
		}
	}
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (player.collidesWith(platformDownList[i], collisionVector))
		{
			// PROTOTYPE COLLISION Detection

			// collide with top of platformDownList[i]
			if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale()
			&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
				//&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
			{
				if (player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
				{	// this is to prevent reseting velocity when player is jumping from the side Down wards
					player.getMovementComponent()->setY_Velocity(-YVelocity);
					// player collides from the top of the platformDownList[i]
					player.setY(platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale()
						- player.getHeight());		// prevents player from moving past the left side of platformDownList[i]
				}

				if (player.airEnum != STATE_GROUNDED)
				{
					player.landed();
				}
			}
			// end of PROTOTYPE COLLISION DETECTION
		}
	}

	if (player.collidesWith(potion, collisionVector))
	{
		potion.apply(&player);
	}
}

//=============================================================================
// Render game items
//=============================================================================
void SmashRipoff::render()
{

    nebula.draw();                          // add the orion nebula to the scene
    planet.draw();                          // add the planet to the scene
	player.draw();

	//platform.draw();
	platform1.draw();

	potion.draw();
	
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		platformUpList[i].draw();
		platformDownList[i].draw();
	}
	// draw every bullet put inside player

	for (int i = 0; i < MAX_HEALTH; i++)	// Add Players' Health
	{
		if (hunterHealth[i].getActive())	// Checks to see if the heart is active (if it isn't, don't draw it)
		{
			hunterHealth[i].draw();
		}

		if (priestessHealth[i].getActive())
		{
			priestessHealth[i].draw();
		}
	}

	
	if (true)
	{

		// Print message
		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "fps %d, Press ESC to pause", (int)fps);
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 3, GAME_HEIGHT / 8);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Vel: %d", (int)player.getMovementComponent()->getX_Velocity());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Vel: %d", (int)player.getMovementComponent()->getY_Velocity());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 2 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Force: %d", (int)player.getMovementComponent()->getX_Force());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 3 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Force: %d", (int)player.getMovementComponent()->getY_Force());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 4 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "projectiles: %d", (int)player.jumpcooldown);
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 0 * GAME_HEIGHT / 5);
		
		

	} 
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SmashRipoff::releaseAll()
{
    nebulaTexture.onLostDevice();
    gameTexture.onLostDevice();
	playerTexture.onLostDevice();
	projectileTexture.onLostDevice();
	platformTexture.onLostDevice();
	heartTexture.onLostDevice();

	Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SmashRipoff::resetAll()
{
    gameTexture.onResetDevice();
    nebulaTexture.onResetDevice();
	playerTexture.onResetDevice();
	projectileTexture.onResetDevice();
	platformTexture.onResetDevice();
	heartTexture.onResetDevice();

	Game::resetAll();
    return;
}