#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
//-----------------------------------------------
// Useful macros
//-----------------------------------------------

// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }

// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }

// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }

// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }

// Transparent Colour (magenta)
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// Window
const char CLASS_NAME[] = "SmashRipoff";
const char GAME_TITLE[] = "SmashRipoff";
const bool FULLSCREEN = false;					// windowed or fullscreen
const UINT GAME_WIDTH =  1024;					// width of game in pixels
const UINT GAME_HEIGHT = 768;					// height of game in pixels
const float ROTATION_SPEED = 50.0f;

// Game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;					// the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;					// the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;		// minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE;	// maximum time used in calculations
//const float GRAVITY = 6.67428e-11f;
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;
const float GRAVITY = 1000;             // gravitational constant

const int TILE_SIZE = 32;
// const int GRID_WIDTH = GAME_WIDTH / TILE_SIZE;
// const int GRID_HEIGHT = GAME_HEIGHT / TILE_SIZE;

// Graphics images
// --MENU--
const char STAGE_IMAGE[]		= "pictures\\background\\spaceStage.jpg";
const char MENU_IMAGE[]			= "pictures\\background\\menuBackground.png";
const char PAUSE_IMAGE[]		= "pictures\\background\\pauseBackground.png";
const char OPTION_IMAGE[]		= "pictures\\background\\optionBackground.png";
const char HUNTER_IMAGE[]		= "pictures\\background\\hunterBackground.png";
const char PRIESTESS_IMAGE[]	= "pictures\\background\\priestessBackground.png";

// --GUI--
// Hearts, ver. 1
const char HEART_IMAGE[]		= "pictures\\lives\\heartv2.png";
// Hearts, ver. 2 (might have to collate into a sheet to use this version)
const char TEST_HEART_IMAGE3[]	= "pictures\\lives\\3lives.png";
const char TEST_HEART_IMAGE2[]	= "pictures\\lives\\2lives.png";
const char TEST_HEART_IMAGE[]	= "pictures\\lives\\1life.png";

// --GAME--
const char TEXTURES_IMAGE[] =	"pictures\\textures.png";

const char NEBULA_IMAGE[] = "pictures\\orion.jpg";
const char PLAYER_TEXTURE[] = "pictures\\Square.png";
const char PROJECTILE_TEXTURE[] = "pictures\\testprojectile.png";
const char PLATFORM_TEXTURE[] = "pictures\\platform.png";
const char SPEEDPOTION_TEXTURE[] = "pictures\\speedpotion.png";
const char HEALTHPOTION_TEXTURE[] = "pictures\\healthpotion.png";
const char METEOR_TEXTURE[] = "pictures\\meteor.png";

// Key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.

// Menu-related stuff (?)
const UCHAR ESC_KEY      = VK_ESCAPE;       // ESC key
const UCHAR ALT_KEY      = VK_MENU;         // alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // enter key

// Player One (Bounty Hunter)
const UCHAR W_KEY = 0x57;			// W key (Jump)
const UCHAR S_KEY = 0x53;			// S key (Dive)
const UCHAR A_KEY = 0x41;			// A key (Left)
const UCHAR D_KEY = 0x44;			// D key (Right)
const UCHAR R_KEY = 0x52;			// R key (Attack1)
const UCHAR T_KEY = 0x54;			// T key (Attack2)

// Player Two (Priestess)
const UCHAR UP_KEY = VK_UP;				// ^ key (Jump)
const UCHAR DOWN_KEY = VK_DOWN;			// v key (Dive)
const UCHAR LEFT_KEY = VK_LEFT;			// < key (Left)
const UCHAR RIGHT_KEY = VK_RIGHT;		// > key (Right)
const UCHAR ATTACK_KEY = VK_OEM_PERIOD;	// . key (Attack1)
const UCHAR ATTACK2_KEY = VK_OEM_COMMA;	// , key (Attack2)

// Additional Stuff
const UCHAR B_KEY = 0x42;		// B key
const UCHAR C_KEY = 0x43;		// C key
const UCHAR E_KEY = 0x45;		// E key
const UCHAR F_KEY = 0x46;		// F key
const UCHAR G_KEY = 0x47;		// G key
const UCHAR H_KEY = 0x48;		// H key
const UCHAR I_KEY = 0x49;		// I key
const UCHAR J_KEY = 0x4A;		// J key
const UCHAR K_KEY = 0x4B;		// K key
const UCHAR L_KEY = 0x4C;		// L key
const UCHAR M_KEY = 0x4D;		// M key
const UCHAR N_KEY = 0x4E;		// N key
const UCHAR O_KEY = 0x4F;		// O key
const UCHAR P_KEY = 0x50;		// P key
const UCHAR Q_KEY = 0x51;		// Q key
const UCHAR U_KEY = 0x55;		// U key
const UCHAR V_KEY = 0x56;		// V key
const UCHAR X_KEY = 0x58;		// X key
const UCHAR Y_KEY = 0x59;		// Y key
const UCHAR Z_KEY = 0x5A;		// Z key

// enum WEAPON {TORPEDO, SHIP, PLANET};

//List declaration
const int   NO_PLATFORMS = 2; //number of platforms

#endif // _CONSTANTS_H