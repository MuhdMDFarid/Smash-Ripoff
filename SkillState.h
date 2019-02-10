//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef  _SkillState_H
#define _SkillState_H
#define WIN32_LEAN_AND_MEAN

#include "Skill.h"
#include "constants.h"

class SkillState
{

public:
	SkillState();
	~SkillState();
	virtual SkillState* handleInput(Skill& skill, Input* input /*other input*/) = 0;
	virtual void update(Skill& skill, float frameTime) = 0;
	virtual void enter(Skill& skill) = 0;
	virtual void exit(Skill& skill) = 0;
	void interrupt(Skill& skill);
};

#endif