//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "Movement_Component.h"


Movement_Component::Movement_Component()
{
}

Movement_Component::~Movement_Component()
{
}

void Movement_Component::receive(int message)
{
}

void Movement_Component::execute()
{
}

void Movement_Component::setX_Force(float x_force)
{
	X_Force = x_force;
}

void Movement_Component::setY_Force(float y_force)
{
	Y_Force = y_force;
}

void Movement_Component::setX_Velocity(float x_velocity)
{
	X_Velocity = x_velocity;
}

void Movement_Component::setY_Velocity(float y_velocity)
{
	Y_Velocity = y_velocity;
}

void Movement_Component::addX_Force(float x_force)
{
	X_Force += x_force;
	if (X_Force > MovementNS::MAX_FORCE)
	{
		X_Force = MovementNS::MAX_FORCE;
	}
	else if (X_Force < -MovementNS::MAX_FORCE)
	{
		X_Force = -MovementNS::MAX_FORCE;
	}
	//setX_Force(X_Force + x_force);
}

void Movement_Component::addY_Force(float y_force)
{
	Y_Force += y_force;
	if (Y_Force > MovementNS::MAX_FORCE)
	{
		Y_Force = MovementNS::MAX_FORCE;
	}
	else if (Y_Force < -MovementNS::MAX_FORCE)
	{
		Y_Force = -MovementNS::MAX_FORCE;
	}
	//setY_Force(Y_Force + y_force);
}