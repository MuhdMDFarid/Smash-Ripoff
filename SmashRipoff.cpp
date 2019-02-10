//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "SmashRipoff.h"
#include "MenuState.h"
#include "HunterDeathState.h"
#include "PriestessDeathState.h"

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
	// throws GameError
    Game::initialize(hwnd);

	// --Menu Assets--
	// Initializes all the necessary assets
	if (!menuBackgroundTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu's background texture"));

	if (!menuBackground.initialize(graphics, 0, 0, 0, &menuBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu's background"));


	// --Pause Assets--
	// Initializes all the necessary assets
	if (!pauseBackgroundTexture.initialize(graphics, PAUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause's background texture"));

	if (!pauseBackground.initialize(graphics, 0, 0, 0, &pauseBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause's background"));


	// --Option Assets--
	// Initializes all the necessary assets
	if (!optionBackgroundTexture.initialize(graphics, OPTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing option's background texture"));

	if (!optionBackground.initialize(graphics, 0, 0, 0, &optionBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing option's background"));

	
	// --Hunter Death Assets--
	// Initializes all the necessary assets
	if (!hunterDeathTexture.initialize(graphics, HUNTER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hunter's background texture"));

	if (!hunterBackground.initialize(graphics, 0, 0, 0, &hunterDeathTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hunter's background"));


	// --Priestess Death Assets--
	// Initializes all the necessary assets
	if (!priestessDeathTexture.initialize(graphics, PRIESTESS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hunter's background texture"));

	if (!priestessBackground.initialize(graphics, 0, 0, 0, &priestessDeathTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hunter's background"));

	
	// --Fonts--
	// Initialize DirectX font
	if (!titleFont.initialize(graphics, gameNS::tPoint_Size, false, false, gameNS::tFont))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	titleFont.setFontColor(gameNS::tFont_Color);

	// Initialize DirectX font
	if (!buttonFont.initialize(graphics, gameNS::bPoint_Size, false, false, gameNS::bFont))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	buttonFont.setFontColor(gameNS::bFont_Color);

	
	// --Buttons--
	// Initializes all the necessary assets
	if (!buttonTexture.initialize(graphics, BUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button's texture"));

	/*
	if (!button.initialize(this, buttonNS::WIDTH, buttonNS::HEIGHT, buttonNS::TEXTURE_COLS, &buttonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button"));
	*/
	if (!startButton.initialize(this, buttonNS::WIDTH, buttonNS::HEIGHT, buttonNS::TEXTURE_COLS, &buttonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing start button"));
	if (!optionButton.initialize(this, buttonNS::WIDTH, buttonNS::HEIGHT, buttonNS::TEXTURE_COLS, &buttonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing option button"));
	if (!resumeButton.initialize(this, buttonNS::WIDTH, buttonNS::HEIGHT, buttonNS::TEXTURE_COLS, &buttonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing resume button"));
	if (!exitButton.initialize(this, buttonNS::WIDTH, buttonNS::HEIGHT, buttonNS::TEXTURE_COLS, &buttonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing exit button"));


	// --GAME--
    // nebula texture
    if (!nebulaTexture.initialize(graphics, STAGE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTexture.initialize(graphics, TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	nebula.setScale(5);

    // planet
    if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	if (!hunterTexture.initialize(graphics, HUNTER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hunter textures"));

	if (!priestessTexture.initialize(graphics, PRIESTESS_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Priestess textures"));

	// -- Hunter --
	// Initializes all the necessary assets
	if (!hunter.initialize(this, 32, 32, PlayerNS::TEXTURE_COLS, &hunterTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hunter"));	

	PlayerInput_Component* Hinput= new PlayerInput_Component();
	Hinput->bindUp(W_KEY);
	Hinput->bindDown(S_KEY);
	Hinput->bindLeft(A_KEY);
	Hinput->bindRight(D_KEY);
	Hinput->bindNormal(R_KEY);
	Hinput->bindSpecial(T_KEY);
	hunter.setPK(Hinput);

	// -- Priestess --
	// Initializes all the necessary assets
	if (!priestess.initialize(this, 32, 32, PlayerNS::TEXTURE_COLS, &priestessTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));

	PlayerInput_Component* Pinput = new PlayerInput_Component();
	Pinput->bindUp(UP_KEY);
	Pinput->bindDown(DOWN_KEY);
	Pinput->bindLeft(LEFT_KEY);
	Pinput->bindRight(RIGHT_KEY);
	Pinput->bindNormal(PERIOD_KEY);
	Pinput->bindSpecial(COMMA_KEY);
	priestess.setPK(Pinput);
	priestess.setX(GAME_WIDTH / 2);

	// projectile texture
	if (!projectileTexture.initialize(graphics, PROJECTILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile texture"));

	/// platform texture
	if (!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

	if (!platform1.initialize(this, GAME_WIDTH, 32, 1, &platformTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	platform1.setX(0);
	platform1.setY(GAME_HEIGHT-platform1.getHeight()-200);

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

	// TEMP POTION texture
	if (!potionTexture.initialize(graphics, SPEEDPOTION_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SPD POT textures"));

	if (!potion.initialize(this, 113, 113, 1, &potionTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing potion"));
	potion.setScale(0.5);
	potion.setX(GAME_WIDTH/2 - potion.getScale()*potion.getWidth());
	potion.setY(GAME_HEIGHT/2 - potion.getScale()*potion.getWidth());

	// --Menu-- (Game has to start off with this state)
	this->pushState(new MenuState(this));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SmashRipoff::update()
{
	// --States--
	this->getCurrentState()->handleInput(input);
	this->getCurrentState()->update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void SmashRipoff::ai()
{
	// --States--
	this->getCurrentState()->ai();
}

//=============================================================================
// Handle collisions
//=============================================================================
void SmashRipoff::collisions()
{
	// --States--
	this->getCurrentState()->collisions();

	//VECTOR2 collisionVector;

	// HITBOX collision
	//if (!player.skill->Hitboxlist.empty())
	//{
	//	for (std::vector<SkillHitbox*>::iterator it = player.skill->Hitboxlist.begin(); it != player.skill->Hitboxlist.end(); )
	//	{

	//			if (platformUpList[1].collidesWith(*(*it)->hitbox, collisionVector))
	//			{
	//				player.getMovementComponent()->setX_Velocity(player.playerface*(*it)->hitbox->getKnockback().x);
	//				player.getMovementComponent()->setY_Velocity((*it)->hitbox->getKnockback().y);

	//				//player.knockback((*it)->hitbox->getKnockback());

	//			}
	//			it++;

	//	}
	//}

	// END OF HITBOX COLLISION

	// platform collision
	//if(player.collidesWith(platform1,collisionVector))
	//{
	//	// PROTOTYPE COLLISION Detection

	//	// collide with top of platform1
	//	if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platform1.getCenterY() + platform1.getEdge().top*platform1.getScale()
	//		&& player.getCenterY() + player.getEdge().top*player.getScale() < platform1.getCenterY() + platform1.getEdge().top*platform1.getScale())
	//	{
	//		// player collides from the top of the platform1
	//		player.setY(platform1.getCenterY() + platform1.getEdge().top*platform1.getScale()
	//			- player.getHeight());		// prevents player from moving past the left side of platform1

	//		if (player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
	//		{	// this is to prevent reseting velocity when player is jumping from the side up wards
	//			player.getMovementComponent()->setY_Velocity(0);
	//		}

	//		//player.setJump(true);
	//		//player.grounded = true;
	//		if (player.airEnum != STATE_GROUNDED)
	//		{
	//			player.landed();
	//		}
	//	}

	//	else if (player.getCenterX() + player.getEdge().right*player.getScale() >= platform1.getCenterX() + platform1.getEdge().left*platform1.getScale()
	//		&& player.getCenterX() + player.getEdge().left*player.getScale() < platform1.getCenterX() + platform1.getEdge().left*platform1.getScale())
	//	{
	//		// player collides from the left side of platform1
	//		player.setX(platform1.getCenterX() + platform1.getEdge().left*platform1.getScale()
	//			- player.getWidth());		// prevents player from moving past the right side of platform1

	//		if (player.getMovementComponent()->getX_Velocity() > 0)		// if player is moving towards right it sets velocity to 0
	//		{
	//			player.getMovementComponent()->setX_Velocity(0);
	//		}
	//	}

	//	else if (player.getCenterX() + player.getEdge().left*player.getScale() <= platform1.getCenterX() + platform1.getEdge().right*platform1.getScale()
	//		&& player.getCenterX() + player.getEdge().right*player.getScale() > platform1.getCenterX() + platform1.getEdge().right*platform1.getScale())
	//	{
	//		// player collides from right side of platform1
	//		player.setX(platform1.getCenterX() + platform1.getEdge().right*platform1.getScale());		// prevents player from moving past the left side of platform1

	//		if (player.getMovementComponent()->getX_Velocity() < 0)		// if player is moving towards left it sets velocity to 0
	//		{
	//			player.getMovementComponent()->setX_Velocity(0);
	//		}
	//	}

	//	else if (player.getCenterY() + player.getEdge().top*player.getScale() <= platform1.getCenterY() + platform1.getEdge().bottom*platform1.getScale()
	//		&& player.getCenterY() + player.getEdge().bottom*player.getScale() > platform1.getCenterY() + platform1.getEdge().bottom*platform1.getScale())
	//	{
	//		// player collides from the bottom of the platform1
	//		player.setY(platform1.getCenterY() + platform1.getEdge().bottom*platform1.getScale());

	//		if (player.getMovementComponent()->getY_Velocity() < 0)		// if player is moving upwards it sets velocity to 0...
	//		{	// this is to prevent player from keeping upwards velocity when hitting the bottom of plat
	//			player.getMovementComponent()->setY_Velocity(0);
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
	//	}*/
	//}
	//else			// If not colliding with platforms 
	//{
	//	if (player.airEnum != STATE_AIRBORNE)
	//	{
	//		player.fall();
	//	}

	//}
	//for (int i = 0; i < NO_PLATFORMS; i++)
	//{
	//	if (player.collidesWith(platformUpList[i], collisionVector))
	//	{
	//		// PROTOTYPE COLLISION Detection

	//		// collide with top of platformUpList[i]
	//		if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platformUpList[i].getCenterY() + platformUpList[i].getEdge().top*platformUpList[i].getScale()
	//			&& player.getCenterY() + player.getEdge().top*player.getScale() < platformUpList[i].getCenterY() + platformUpList[i].getEdge().top*platformUpList[i].getScale())
	//		{

	//			if (player.getMovementComponent()->getY_Velocity() >= 0)		// if player is moving downwards it sets velocity to 0...
	//			{	// this is to prevent reseting velocity when player is jumping from the side up wards
	//				player.getMovementComponent()->setY_Velocity(0);
	//				// player collides from the top of the platformUpList[i]
	//				player.setY(platformUpList[i].getCenterY() + platformUpList[i].getEdge().top*platformUpList[i].getScale()
	//					- player.getHeight());		// prevents player from moving past the left side of platformUpList[i]
	//			}

	//			if (player.airEnum != STATE_GROUNDED)
	//			{
	//				player.landed();
	//			}
	//		}
	//		// end of PROTOTYPE COLLISION DETECTION
	//	}
	//}
	//for (int i = 0; i < NO_PLATFORMS; i++)
	//{
	//	if (player.collidesWith(platformDownList[i], collisionVector))
	//	{
	//		// PROTOTYPE COLLISION Detection

	//		// collide with top of platformDownList[i]
	//		if (player.getCenterY() + player.getEdge().bottom*player.getScale() >= platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale()
	//		&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
	//			//&& player.getCenterY() + player.getEdge().top*player.getScale() < platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale())
	//		{
	//			if (player.getMovementComponent()->getY_Velocity() > 0)		// if player is moving downwards it sets velocity to 0...
	//			{	// this is to prevent reseting velocity when player is jumping from the side Down wards
	//				player.getMovementComponent()->setY_Velocity(-YVelocity);
	//				// player collides from the top of the platformDownList[i]
	//				player.setY(platformDownList[i].getCenterY() + platformDownList[i].getEdge().top*platformDownList[i].getScale()
	//					- player.getHeight());		// prevents player from moving past the left side of platformDownList[i]
	//			}

	//			if (player.airEnum != STATE_GROUNDED)
	//			{
	//				player.landed();
	//			}
	//		}
	//		// end of PROTOTYPE COLLISION DETECTION
	//	}
	//}

	//if (player.collidesWith(potion, collisionVector))
	//{
	//	potion.apply(&player);
	//}
}

//=============================================================================
// Render game items
//=============================================================================
void SmashRipoff::render()
{
	// --States--
	this->getCurrentState()->draw();

	/// OLD draw
	//nebula.draw();                          // add the orion nebula to the scene
	//planet.draw();                          // add the planet to the scene
	//player.draw();

	//platform.draw();
	//platform1.draw();

	//potion.draw();

	//for (int i = 0; i < NO_PLATFORMS; i++)
	//{
	//	platformUpList[i].draw();
	//	platformDownList[i].draw();
	//}
	//for (int i = 0; i < MAX_HEALTH; i++)	// Add Players' Health
	//{
	//	if (hunterHealth[i].getActive())	// Checks to see if the heart is active (if it isn't, don't draw it)
	//	{
	//		hunterHealth[i].draw();
	//	}

	//	if (priestessHealth[i].getActive())
	//	{
	//		priestessHealth[i].draw();
	//	}
	//}


	//if (true)
	//{

	//	// Print message
	//	_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "fps %d, Press ESC to pause", (int)fps);
	//	dxFont.printC(gameNS::buffer, GAME_WIDTH / 3, GAME_HEIGHT / 8);

	//	_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Vel: %d", (int)player.getMovementComponent()->getX_Velocity());
	//	dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, GAME_HEIGHT / 5);

	//	_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Vel: %d", (int)player.getMovementComponent()->getY_Velocity());
	//	dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 2 * GAME_HEIGHT / 5);

	//	_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "X-Force: %d", (int)player.getMovementComponent()->getX_Force());
	//	dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 3 * GAME_HEIGHT / 5);

	//	_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "Y-Force: %d", (int)player.getMovementComponent()->getY_Force());
	//	dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 4 * GAME_HEIGHT / 5);

	//	_snprintf_s(gameNS::buffer, gameNS::BUF_SIZE, "projectiles: %d", (int)player.jumpcooldown);
	//	dxFont.printC(gameNS::buffer, GAME_WIDTH / 2, 0 * GAME_HEIGHT / 5);

	///
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SmashRipoff::releaseAll()
{
	/// OLD CODE
	/*nebulaTexture.onLostDevice();
	gameTexture.onLostDevice();
	playerTexture.onLostDevice();
	projectileTexture.onLostDevice();
	platformTexture.onLostDevice();
	heartTexture.onLostDevice();

	Game::releaseAll();
	return;*/
	///
	Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SmashRipoff::resetAll()
{
	/// OLD CODE
	/*gameTexture.onResetDevice();
	nebulaTexture.onResetDevice();
	playerTexture.onResetDevice();
	projectileTexture.onResetDevice();
	platformTexture.onResetDevice();
	heartTexture.onResetDevice();

	Game::resetAll();
	return;*/
	///
	Game::resetAll();
    return;
}

//=============================================================================
// Adds the current state to the top of the vector (game loop goes to that state)
//=============================================================================
void SmashRipoff::pushState(GameState* state)
{
	states.push_back(state);
}

//=============================================================================
// Removes the current state from the top of the vector
//=============================================================================
void SmashRipoff::popState()
{
	// Delete the pointer pointing to the last element
	states.back();
	delete states.back();

	// Deletes the last element in the vector
	states.pop_back();
}

//=============================================================================
// Gets the current state (this is a pointer)
//=============================================================================
GameState* SmashRipoff::getCurrentState()
{
	// If the vector is empty, return a nullptr
	if (states.empty())
		return nullptr;

	// Else, return the last element in the vector
	else
		return states.back();
}

//=============================================================================
// Removes everything from the vector
//=============================================================================
void SmashRipoff::deleteState()
{
	states.clear();
}

//=============================================================================
// Resets every asset
//=============================================================================
void SmashRipoff::resetGame()
{
	// Health
	hunterHP = 2;
	priestessHP = 2;

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		priestessHealth[i].setActive(true);
		hunterHealth[i].setActive(true);
	}

	// Potions
	hunter.speedmultiplier = 1;
	hunter.agilityduration = 0;
	priestess.speedmultiplier = 1;
	priestess.agilityduration = 0;

	// Player position
	hunter.setX(0);
	hunter.setY(0);

	priestess.setX(GAME_WIDTH-priestess.getWidth() * priestess.getScale());
	priestess.setY(0);
}