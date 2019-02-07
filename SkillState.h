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