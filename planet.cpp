//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "planet.h"

//=============================================================================
// Default Constructor
//=============================================================================
Planet::Planet() : Entity()
{
    spriteData.x    = planetNS::X;              // location on screen
    spriteData.y    = planetNS::Y;
    radius          = planetNS::COLLISION_RADIUS;
    mass            = planetNS::MASS;
    startFrame      = planetNS::START_FRAME;    // first frame of ship animation
    endFrame        = planetNS::END_FRAME;      // last frame of ship animation
    setCurrentFrame(startFrame);
}