// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 SmashRipoff.cpp v1.0
// This class is the core of the game

#include "SmashRipoff.h"

//=============================================================================
// Constructor
//=============================================================================
SmashRipoff::SmashRipoff()
{}

//=============================================================================
// Destructor
//=============================================================================
SmashRipoff::~SmashRipoff()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void SmashRipoff::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

    // planet
    if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/4);
    ship1.setY(GAME_HEIGHT/4);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
    // ship2
    if (!ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
    ship2.setFrames(shipNS::SHIP2_START_FRAME, shipNS::SHIP2_END_FRAME);
    ship2.setCurrentFrame(shipNS::SHIP2_START_FRAME);
    ship2.setX(GAME_WIDTH - GAME_WIDTH/4);
    ship2.setY(GAME_HEIGHT/4);
    ship2.setVelocity(VECTOR2(-shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)


															   // main game textures
	if (!playerTextures.initialize(graphics, SQUARE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!player.initialize(this, 32, 32,PlayerNS::TEXTURE_COLS, &playerTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));	


	// projectile texture
	if (!projectileTexture.initialize(graphics, PROJECTILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile texture"));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SmashRipoff::update()
{
	if (input->getMouseLButton())
	{
		player.shoot(this, input->getMouseX(), input->getMouseY(),&projectileTexture);
		//shootable = false;
		//Projectile p;
		//	if (!p.initialize(this, 32, 32, shipNS::TEXTURE_COLS, &gameTextures))
		//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
		//p.setFrames(40, 43);
		//p.setCurrentFrame(40);
		//p.setY(player.getY());
		//p.setX(player.getX());
		//graphics->spriteBegin();
		//p.draw();
		//graphics->spriteEnd();
		//projectilevec.push_back(p);
		
/*
		player.setX(input->getMouseX());
		player.setY(input->getMouseY());*/
		//player.shoot((input->getMouseX()-player.getX()),(input->getMouseY()-player.getY()));
	}


	// GRAVITY SIMULATION
	player.getMovementComponent()->setY_Velocity(player.getMovementComponent()->getY_Velocity()+GRAVITY * frameTime);


	if (input->isKeyDown(VK_SPACE))
	{
		player.getMovementComponent()->setX_Velocity(100);
	}

	if (input->isKeyDown(W_KEY))	//jump
	{
		//player.move(0, -player.getSpeed());
		if (player.iscanJump())
		{
			player.getMovementComponent()->setY_Velocity(-250);
			player.setJump(false);
		}
	}
	else if (input->isKeyDown(S_KEY))
	{
		player.move(0, player.getSpeed());
		//player.getMovementComponent()->setY_Force(100);
	}
	else
	{
		player.getMovementComponent()->setY_Force(0);
	}

	if (input->isKeyDown(A_KEY))
	{
		//player.move(-player.getSpeed(), 0);
		player.getMovementComponent()->setX_Force(-player.getSpeed());
	}
	else if (input->isKeyDown(D_KEY))
	{
		//player.move(player.getSpeed(), 0);
		player.getMovementComponent()->setX_Force(player.getSpeed());
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
    ship1.update(frameTime);
    ship2.update(frameTime);
	player.update(frameTime);

	//update every bullet
	
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
    // if collision between ship and planet
    if(ship1.collidesWith(planet, collisionVector))
    {
        // bounce off planet
        ship1.bounce(collisionVector, planet);
        //ship1.damage(PLANET);
    }
    if(ship2.collidesWith(planet, collisionVector))
    {
        // bounce off planet
        ship2.bounce(collisionVector, planet);
        //ship2.damage(PLANET);
    }
    // if collision between ships
    if(ship1.collidesWith(ship2, collisionVector))
    {
        // bounce off ship
        ship1.bounce(collisionVector, ship2);
        //ship1.damage(SHIP);
        // change the direction of the collisionVector for ship2
        ship2.bounce(collisionVector*-1, ship1);
        //ship2.damage(SHIP);
    }
	if (player.collidesWith(ship1, collisionVector))
	{
		player.bounce(collisionVector, ship1);
		
		ship1.bounce(collisionVector*-1, player);
		//ship1.damage(SHIP);
	}
	if (player.collidesWith(ship2, collisionVector))
	{
		player.bounce(collisionVector, ship2);

		ship2.bounce(collisionVector*-1, player);
		//ship2.damage(SHIP);
	}
}

//=============================================================================
// Render game items
//=============================================================================
void SmashRipoff::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    nebula.draw();                          // add the orion nebula to the scene
    planet.draw();                          // add the planet to the scene
    ship1.draw();                           // add the spaceship to the scene
    ship2.draw();                           // add the spaceship to the scene
	player.draw();

	// draw every bullet put inside player

	if (true)
	{

		// Print message
		//_snprintf_s(buffer, BUF_SIZE, "test %d ", (int)fps);
		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Vel: %d", (int)player.getMovementComponent()->getX_Velocity());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Vel: %d", (int)player.getMovementComponent()->getY_Velocity());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 2 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Force: %d", (int)player.getMovementComponent()->getX_Force());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 3 * GAME_HEIGHT / 5);

		_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Force: %d", (int)player.getMovementComponent()->getY_Force());
		dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 4 * GAME_HEIGHT / 5);

		//_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "projectiles: %d", (int)player.projectilelist.size());
		//dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 0 * GAME_HEIGHT / 5);
		
		

	}

    graphics->spriteEnd();                  // end drawing sprites


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

