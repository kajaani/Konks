#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Platform
{
public:
	Platform();		
	void spawnPlatform(Layer *layer, Vec2 playerPosition);
	void setPosition(Vec2 newPos);

protected:
	Vec2 position;
};