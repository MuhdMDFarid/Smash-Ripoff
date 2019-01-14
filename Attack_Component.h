#ifndef _ATTACK_COMPONENT_H               // Prevent multiple definitions if this 
#define _ATTACK_COMPONENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Component.h"

class Attack_Component: public Component
{
private:
	
public:
	Attack_Component();
	~Attack_Component();
	virtual void receive(int message);
	virtual void execute()=0;
};

#endif