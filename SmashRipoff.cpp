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
	if (!titleFont.initialize(graphics, gameNS::POINT_SIZE, false, false, "Times New Roman"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	titleFont.setFontColor(gameNS::FONT_COLOR);

	// Initialize DirectX font
	if (!buttonFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// Set DirectX font color
	buttonFont.setFontColor(gameNS::FONT_COLOR);


	// --GAME--
    // nebula texture
    if (!nebulaTexture.initialize(graphics, STAGE_IMAGE))
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

	if (!playerTexture.initialize(graphics, PLAYER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));

	if (!player.initialize(this, 32, 32, PlayerNS::TEXTURE_COLS, &playerTexture))
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

	// TEMP POTION texture
	if (!potionTexture.initialize(graphics, SPEEDPOTION_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SPD POT textures"));

	if (!potion.initialize(this, 113, 113, 1, &potionTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing potion"));
	potion.setScale(0.5);
	potion.setX(GAME_WIDTH/2 - potion.getScale()*potion.getWidth());
	potion.setY(GAME_HEIGHT/2 - potion.getScale()*potion.getWidth());

	// --Menu--
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
	this->getCurrentState()->ai();
}

//=============================================================================
// Handle collisions
//=============================================================================
void SmashRipoff::collisions()
{
	this->getCurrentState()->collisions();
}

//=============================================================================
// Render game items
//=============================================================================
void SmashRipoff::render()
{
	// --States--
	this->getCurrentState()->draw();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SmashRipoff::releaseAll()
{
	Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SmashRipoff::resetAll()
{
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