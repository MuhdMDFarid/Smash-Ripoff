#pragma once
#include "Platform.h"
class RotatingPlatform : public Platform
{
public:
	RotatingPlatform();
	~RotatingPlatform();
	void update(float frameTime);
};

