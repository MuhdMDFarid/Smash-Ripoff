//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _MOVEMENT_COMPONENT_H               // Prevent multiple definitions if this 
#define _MOVEMENT_COMPONENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Component.h"

namespace MovementNS
{
	const int MAX_FORCE = 200;
	const int MAX_VELOCITY = 300;
	const float FRICTION = 0.8;
	const float FRICTION_CONST = 200;
}

class Movement_Component : public Component
{

private:

	// !! ENTITY CLASS HAS SOMESORT OF VARIABLE RELATED TO FORCE AND GRAVITY
	float X_Force = 0;
	float Y_Force = 0;
	float X_Velocity = 0;
	float Y_Velocity = 0;
	float Mass = 1;

public:

	// Constructor
	Movement_Component();

	// Destructor
	~Movement_Component();

	// ======================
	// Functions
	// ======================
	void receive(int message);
	void execute();

	// GET
	float getX_Force() { return X_Force; }
	float getY_Force() { return Y_Force; }
	float getX_Velocity() { return X_Velocity; }
	float getY_Velocity() { return Y_Velocity; }

	// SET
	void setX_Force(float x_force);	
	void setY_Force(float y_force);
	void setX_Velocity(float x_velocity);
	void setY_Velocity(float y_velocity);

	// ADD
	void addX_Force(float x_force);
	void addY_Force(float y_force);

	//void update(float frametime)

};

#endif // _MOVEMENT_COMPONENT_H