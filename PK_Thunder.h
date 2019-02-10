//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _PK_Thunder_H
#define _PK_Thunder_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "Player.h"
//#include "Melee_Hitbox.h"
#include "Projectile_Hitbox.h"
#include "Controlled_Projectile_Hitbox.h"
#include "SkillState.h"
#include "Skill.h"


class SkillState;

// the actual move 
class PK_Thunder : public Skill
{
private:
	/*SkillState* state;
	bool finished;*/
public:
	//std::vector<SkillHitbox*> Hitboxlist;
	//Attack_Hitbox* newhitbox;
	// 

//public:
	PK_Thunder();
	~PK_Thunder();
	void execute(Player& player);
	//void update(Player& player,float frameTime);		// maybe don't need
	void cancel();
	bool isFinished() { return finished; }
	//void draw();
	//float finalangle(float alpha,int xdirection);
};

#endif