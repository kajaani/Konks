#include "Platform.h"

using namespace cocos2d;

Platform::Platform()
{
	position = Vec2(0, 0);
}


void Platform::setPosition(Vec2 newPos)
{
	position = newPos;
}