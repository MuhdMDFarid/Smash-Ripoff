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