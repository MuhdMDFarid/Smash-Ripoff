#include "RotatingPlatform.h"



RotatingPlatform::RotatingPlatform()
{
}


RotatingPlatform::~RotatingPlatform()
{
}

void RotatingPlatform::update(float frameTime)
{
	setRadians(getRadians() - platformNS::ROTATION_RATE * frameTime);
	Platform::update(frameTime);
}
