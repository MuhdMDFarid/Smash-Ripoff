#ifndef _COMPONENT_H               // Prevent multiple definitions if this 
#define _COMPONENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Component
{
public:
	Component();
	~Component();
	virtual void receive(int message) = 0;
	//virtual void execute() = 0;
};

#endif