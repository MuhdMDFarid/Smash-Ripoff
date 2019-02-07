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
