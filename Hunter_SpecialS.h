#ifndef _Hunter_SpecialS_H
#define _Hunter_SpecialS_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "Player.h"
#include "Melee_Hitbox.h"
#include "SkillState.h"
#include "Skill.h"
//
//struct SkillHitbox 
//{
//	float spawndelay;
//	Attack_Hitbox* hitbox;
//};

//enum S_State
//{
//	STATE_ACTIVE,
//	STATE_FINISHED
//};

class SkillState;

// the actual move 
class Hunter_SpecialS : public Skill
{
private:
	/*SkillState* state;
	bool finished;*/
public:
	//std::vector<SkillHitbox*> Hitboxlist;
	//Attack_Hitbox* newhitbox;
	// 

//public:
	Hunter_SpecialS();
	~Hunter_SpecialS();
	void execute(Player& player);
	//void update(Player& player,float frameTime);		// maybe don't need
	void cancel();
	bool isFinished() { return finished; }
	//void draw();
	//float finalangle(float alpha,int xdirection);
};

#endif