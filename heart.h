#ifndef _HEART_H
#define _HEART_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{
	const int WIDTH = 32;				   // image width
	const int HEIGHT = 32;                 // image height
	const int X = 0;						// location on screen
	const int Y = 0;
}

// inherits from Entity class
class Heart : public Entity
{
public:
	// Constructor
	Heart();
};
#endif // _HEART_H