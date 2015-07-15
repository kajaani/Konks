#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Platform
{
public:
	Platform();		
	void setPosition(Vec2 newPos);

protected:
	Vec2 position;
};