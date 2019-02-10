//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "heart.h"

//=============================================================================
// Default Constructor
//=============================================================================
Heart::Heart() : Entity()
{
	spriteData.width = heartNS::WIDTH;           // size of asteroid
	spriteData.height = heartNS::HEIGHT;
	spriteData.x = heartNS::X;                   // location on screen
	spriteData.y = heartNS::Y;
	spriteData.rect.bottom = heartNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = heartNS::WIDTH;
}