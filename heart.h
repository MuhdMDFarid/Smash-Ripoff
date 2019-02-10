//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _HEART_H
#define _HEART_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{
	const int WIDTH = 32;					// image width
	const int HEIGHT = 32;					// image height
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