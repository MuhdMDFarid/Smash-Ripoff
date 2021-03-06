//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "SmashRipoff.h"
#include "MenuState.h"
#include "HunterDeathState.h"
#include "PriestessDeathState.h"
#include <string>
#include <ctime>

#include "Hunter_NormalS.h"
#include "Hunter_SpecialS.h"
#include "PK_Fire.h"
#include "PK_Thunder.h"

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
	int randomx1;
	int randomx2;
	int randomy1;
	int randomy2;
	srand(time(NULL));
	randomx1 = rand() % (GAME_WIDTH);
	randomx2 = rand() % (GAME_WIDTH);
	randomy1 = rand() % (GAME_HEIGHT);
	randomy2 = rand() % (GAME_HEIGHT);

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

	std::vector<Skill*> skillset;
	skillset.push_back(new Hunter_NormalS());
	skillset.push_back(new Hunter_SpecialS());
	hunter.setSkillSet(skillset);

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
	
	skillset.clear();
	skillset.push_back(new PK_Fire());
	skillset.push_back(new PK_Thunder());
	priestess.setSkillSet(skillset);

	resetPlayersPosition();

	// projectile texture
	if (!projectileTexture.initialize(graphics, PROJECTILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile texture"));

	/// platform texture
	if (!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

	if (!platform.initialize(this, 320, 32, 1, &platformTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	platform.setX(GAME_WIDTH * 1 / 3);
	platform.setY(GAME_HEIGHT * 1 / 2);

	if (!platform1.initialize(this, GAME_WIDTH * 4 / 6.5, 32, 1, &platformTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	platform1.setX(GAME_WIDTH * 1 / 5);
	platform1.setY(GAME_HEIGHT * 2 / 3 - platform1.getHeight());


	// Hearts
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		if (!hunter.Health[i].initialize(this, heartNS::WIDTH, heartNS::HEIGHT, 0, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hearts"));
		// Makes the image bigger
		hunter.Health[i].setScale(2);
		// Sets it to the left of the screen (player 1)
		hunter.Health[i].setX(heartNS::WIDTH * i);			
		// Sets it to the bottom of the screen (ensures that it doesn't go below the screen)
		hunter.Health[i].setY(GAME_HEIGHT - (heartNS::HEIGHT * hunter.Health[i].getScale()));
	}

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		if (!priestess.Health[i].initialize(this, heartNS::WIDTH, heartNS::HEIGHT, 0, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hearts"));
		// Makes the image bigger
		priestess.Health[i].setScale(2);
		// Sets it to the right of the screen (player 2)
		priestess.Health[i].setX(GAME_WIDTH - ((heartNS::WIDTH * (i + 1)) + heartNS::WIDTH));
		// Sets it to the bottom of the screen (ensures that it doesn't go below the screen)
		priestess.Health[i].setY(GAME_HEIGHT - (heartNS::HEIGHT * priestess.Health[i].getScale()));
	}

	//hk
	// for moving platforms
	for (int i = 0; i < NO_PLATFORMS; i++)
	{
		if (!platformUpList[i].initialize(this, 160, 32, 1, &platformTexture))	// 1 since texture has only one image
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
		platformUpList[i].setDegrees(0);
		platformUpList[i].setX(8 * GAME_WIDTH / 10);
		platformUpList[i].setY(GAME_HEIGHT / 2 * (NO_PLATFORMS - i));
		platformUpList[i].setVelocity(VECTOR2(0, -TILE_SIZE * 4));

		if (!platformDownList[i].initialize(this, 160, 32, 1, &platformTexture))	// 1 since texture has only one image
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
		platformDownList[i].setDegrees(0);
		platformDownList[i].setX(1 * GAME_WIDTH / 10);
		platformDownList[i].setY(GAME_HEIGHT / 2 * (NO_PLATFORMS - i));
		platformDownList[i].setVelocity(VECTOR2(0, TILE_SIZE * 4));
	}
	// TEMP POTION texture
	if (!speedpotionTexture.initialize(graphics, SPEEDPOTION_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SPD POT textures"));

	if (!healthpotionTexture.initialize(graphics, HEALTHPOTION_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing HP POT textures"));

	if (!speedpotion.initialize(this, 113, 113, 1, &speedpotionTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing potion"));

	if (!healthpotion.initialize(this, 113, 113, 1, &healthpotionTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing potion"));
	speedpotion.setScale(0.5);
	speedpotion.setX(randomx1 - speedpotion.getScale()*speedpotion.getWidth());
	speedpotion.setY(randomy1 - speedpotion.getScale()*speedpotion.getWidth());
	healthpotion.setScale(0.5);
	healthpotion.setX(randomx2 - healthpotion.getScale()*healthpotion.getWidth());
	healthpotion.setY(randomy2 - healthpotion.getScale()*healthpotion.getWidth());

	// landmine textures
	if (!landmineTexture.initialize(graphics, LANDMINE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!landmine.initialize(this, 60, 30, 1, &landmineTexture))	// 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
	landmine.setX(rand() % (int(platform1.getWidth())) + platform1.getX());
	landmine.setY(platform1.getY() - LANDMINE_SIZE);


	//meteor texture
	// Meteor texture
	if (!meteorTexture.initialize(graphics, METEOR_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing meteor texture"));
	if (!meteor.initialize(this, meteorNS::WIDTH, meteorNS::HEIGHT, 1, &meteorTexture))    // 1 since texture has only one image
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing meteor"));
	meteor.setScale(0.5);
	meteor.setDegrees(0);
	meteor.setX(GAME_WIDTH);
	meteor.setY(0);
	meteor.setVelocity(VECTOR2(-meteorNS::SPEED, meteorNS::SPEED));

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

void SmashRipoff::resetPlayersPosition()	// reset player position
{
	// Player position
	hunter.setX(GAME_WIDTH / 4 - hunter.getWidth() * hunter.getScale());
	hunter.setY(0);
	hunter.setX_Velocity(0);
	hunter.setY_Velocity(0);

	priestess.setX(3 * GAME_WIDTH / 4 - priestess.getWidth() * priestess.getScale());
	priestess.setY(0);
	priestess.setX_Velocity(0);
	priestess.setY_Velocity(0);
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
	hunter.HP = 2;
	priestess.HP = 2;

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		priestess.Health[i].setActive(true);
		hunter.Health[i].setActive(true);
	}

	// Potions
	hunter.speedmultiplier = 1;
	hunter.agilityduration = 0;
	priestess.speedmultiplier = 1;
	priestess.agilityduration = 0;

	resetPlayersPosition();		// Player position
}