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
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	nebula.setScale(5);

    // planet
    if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

    // ship
    //if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
    //    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    //ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    //ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    //ship1.setX(GAME_WIDTH/4);
    //ship1.setY(GAME_HEIGHT/4);
    //ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
    //// ship2
    //if (!ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
    //    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
    //ship2.setFrames(shipNS::SHIP2_START_FRAME, shipNS::SHIP2_END_FRAME);
    //ship2.setCurrentFrame(shipNS::SHIP2_START_FRAME);
    //ship2.setX(GAME_WIDTH - GAME_WIDTH/4);
    //ship2.setY(GAME_HEIGHT/4);
    //ship2.setVelocity(VECTOR2(-shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)


	// main game textures
	if (!playerTextures.initialize(graphics, PLAYER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!player.initialize(this, 32, 32,PlayerNS::TEXTURE_COLS, &playerTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));	


	// projectile texture
	if (!projectileTexture.initialize(graphics, PROJECTILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile texture"));

	/// platform texture
	if (!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

	if (!platform.initialize(this, 320, 32, 1, &platformTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	platform.setX(GAME_WIDTH/2);
	platform.setY(GAME_HEIGHT);

	if (!platform1.initialize(this, GAME_WIDTH, 32, 1, &platformTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	platform1.setX(0);
	platform1.setY(GAME_HEIGHT-platform1.getHeight());
	///

	// TEMP POTION texture
	if (!potionTexture.initialize(graphics, SPEEDPOTION_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SPD POT textures"));

	if (!potion.initialize(this, 113, 113, 1, &potionTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing potion"));
	potion.setScale(0.5);
	potion.setX(GAME_WIDTH - TILE_SIZE);
	potion.setY(GAME_HEIGHT - 2*TILE_SIZE);


    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SmashRipoff::update()
{
	player.update(frameTime);

	//player.fall();
	if (platform.getY() <= -platform.getHeight())
		platform.setY(GAME_HEIGHT);
	platform.setY(platform.getY() - TILE_SIZE*4*frameTime);

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

	platform.update(frameTime);	// should this even have update since platforms dont really move
	platform1.update(frameTime);

	potion.update(frameTime);
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
	if(player.collidesWith(platform,collisionVector))
	{
		// PROTOTYPE COLLISION Detection

		// collide with top of platform
		if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platform.getCenterY() + platform.getEdge().top*platform.getScale()
			&& player.getCenterY() + player.getEdge().top*player.getScale() < platform.getCenterY() + platform.getEdge().top*platform.getScale())
		{
			// player collides from the top of the platform
			player.setY(platform.getCenterY() + platform.getEdge().top*platform.getScale()
				- player.getHeight());		// prevents player from moving past the left side of platform

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

		else if (player.getCenterX() + player.getEdge().right*player.getScale() >= platform.getCenterX() + platform.getEdge().left*platform.getScale()
			&& player.getCenterX() + player.getEdge().left*player.getScale() < platform.getCenterX() + platform.getEdge().left*platform.getScale())
		{
			// player collides from the left side of platform
			player.setX(platform.getCenterX() + platform.getEdge().left*platform.getScale()
				- player.getWidth());		// prevents player from moving past the right side of platform

			if (player.getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
			{
				player.getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (player.getCenterX() + player.getEdge().left*player.getScale() <= platform.getCenterX() + platform.getEdge().right*platform.getScale()
			&& player.getCenterX() + player.getEdge().right*player.getScale() > platform.getCenterX() + platform.getEdge().right*platform.getScale())
		{
			// player collides from right side of platform
			player.setX(platform.getCenterX() + platform.getEdge().right*platform.getScale());		// prevents player from moving past the left side of platform

			if (player.getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
			{
				player.getMovementComponent()->setX_Velocity(0);
			}
		}

		else if (player.getCenterY() + player.getEdge().top*player.getScale() <= platform.getCenterY() + platform.getEdge().bottom*platform.getScale()
			&& player.getCenterY() + player.getEdge().bottom*player.getScale() > platform.getCenterY() + platform.getEdge().bottom*platform.getScale())
		{
			// player collides from the bottom of the platform
			player.setY(platform.getCenterY() + platform.getEdge().bottom*platform.getScale());

			if (player.getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
			{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
				player.getMovementComponent()->setY_Velocity(0);
			}
		}
	}
	else if (player.collidesWith(platform1,collisionVector))
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

	// TEMP Potion collision
	if (player.collidesWith(potion, collisionVector))
	{
		// bounce off planet
		potion.apply(&player);
		potion.setVisible(false);
		//ship2.damage(PLANET);
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

	platform.draw();
	platform1.draw();
	potion.draw();
	// draw every bullet put inside player

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

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "projectiles: %d", /*(int)player.projectilelist.size()*/(int)player.jumpcooldown);
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
    gameTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SmashRipoff::resetAll()
{
    gameTextures.onResetDevice();
    nebulaTexture.onResetDevice();
    Game::resetAll();
    return;
}