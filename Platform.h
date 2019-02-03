#ifndef _PLATFORM_H
#define _PLATFORM_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>		// maybe for the multiple collision boxes for weird shaped obstacles

class Platform:public Entity
{
private:
	//std::vector<Hitbox*> hitboxlist;		// for multiple collisionboxes
public:

	// Constructor
	Platform();

	// Destructor
	~Platform();

	// ======================
	// Functions
	// ======================
	bool initialize(Game*gamePtr, int width, int height, int ncols, TextureManager*textureM);
	virtual void draw();
	void update(float frameTime);

};

#endif // _PLATFORM_H