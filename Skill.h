#ifndef _Skill_H
#define _Skill_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "Player.h"
#include "Attack_Hitbox.h"

struct SkillHitbox 
{
	float spawndelay;
	Attack_Hitbox* hitbox;
};

// the actual move 
class Skill
{
public:
	std::vector<SkillHitbox*> Hitboxlist;
	std::vector<Attack_Hitbox*> AHitboxlist;
	Attack_Hitbox* newhitbox;
	//SkillHitbox* newskillhitbox;
	// 

//public:
	Skill();
	~Skill();
	void execute(Player& player);
	void update(Player& player,float frameTime);		// maybe don't need
	void cancel();
	void draw();
};

#endif