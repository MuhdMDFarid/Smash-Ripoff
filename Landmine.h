#ifndef _LANDMINE_H
#define _LANDMINE_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>		// maybe for the multiple collision boxes for weird shaped obstacles
#include "Movement_Component.h"


namespace landmineNS
{

}

class Landmine :public Entity
{
private:


public:
	// Constructor
	Landmine();

	// Destructor
	~Landmine();

	// ======================
	// Functions
	// ======================
	bool initialize(Game*gamePtr, int width, int height, int ncols, TextureManager*textureM);
	virtual void draw();
	void update(float frameTime);
};

#endif
