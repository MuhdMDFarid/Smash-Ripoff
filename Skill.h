//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _Skill_H
#define _Skill_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "Player.h"
#include "Melee_Hitbox.h"
#include "SkillState.h"

struct SkillHitbox 
{
	float spawndelay;
	Hitbox* hitbox;
	//Melee_Hitbox* hitbox;
};

enum S_State
{
	STATE_ACTIVE,
	STATE_FINISHED
};

class SkillState;

namespace SkillNS
{
	// Hunter Normal
	const float HUNTER_NORM_ANG_1 = 35;
	const float HUNTER_NORM_DMG_1 = 20;
	const float HUNTER_NORM_KNB_1 = 25;
	const float HUNTER_NORM_STN_1 = 0.3f;
	const float HUNTER_NORM_LIF_1 = 0.2f;

	const float HUNTER_NORM_ANG_2 = 75;
	const float HUNTER_NORM_DMG_2 = 50;
	const float HUNTER_NORM_KNB_2 = 100;
	const float HUNTER_NORM_STN_2 = 0.5f;
	const float HUNTER_NORM_LIF_2 = 0.2f;

	// Hunter Special	
	const float HUNTER_SPEC_VEL = 50;
	const float HUNTER_SPEC_ACC = 500;
	const float HUNTER_SPEC_ANG = 35;
	const float HUNTER_SPEC_DMG = 10;
	const float HUNTER_SPEC_KNB= 25;
	const float HUNTER_SPEC_STN = 0.1f;
	const float HUNTER_SPEC_LIF = 3;
	const float HUNTER_SPEC_SCA = 0.5f;

	// PK_FIRE
	const float PK_FIRE_XVEL = 200;
	const float PK_FIRE_YVEL = 450;
	const float PK_FIRE_VELCHNG = 50;

	const float PK_FIRE_ANG = 90;
	const float PK_FIRE_DMG = 50;
	const float PK_FIRE_KNB = 69;
	const float PK_FIRE_STN = 0.75f;
	const float PK_FIRE_LIF = 2;
	const float PK_FIRE_SCA = 0.75f;

	// PK_THUNDER
	const float PK_THUNDER_MAX_VEL = 300;
	const float PK_THUNDER_VEL = -300;
	const float PK_THUNDER_ACC = 500;
	const float PK_THUNDER_ANG = 60;
	const float PK_THUNDER_DMG = 69;
	const float PK_THUNDER_KNB = 420;
	const float PK_THUNDER_STN = 2.0f;
	const float PK_THUNDER_LIF = 10;
	const float PK_THUNDER_SCA = 0.75f;

}
// the actual move 
class Skill
{
protected:
	SkillState* state;
	bool finished;
	float endLag;
public:
	std::vector<SkillHitbox*> Hitboxlist;
	Hitbox* newhitbox;
	// 

//public:
	Skill();
	~Skill();
	virtual void execute(Player& player);
	virtual void update(Player& player, float frameTime);		// maybe don't need
	void cancel();
	bool isFinished() { return finished; }
	void draw();
	float finalangle(float alpha,int xdirection);
};

#endif