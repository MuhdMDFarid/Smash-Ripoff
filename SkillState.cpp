//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "SkillState.h"


SkillState::SkillState()
{
}


SkillState::~SkillState()
{
}

void SkillState::interrupt(Skill & skill)	// should be able to be done at any point of time during skill
{
	// interrupt skill
	skill.cancel();
}
