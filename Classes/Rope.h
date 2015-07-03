#pragma once
#include "cocos2d.h"
#include "Definitions.h"
using namespace cocos2d;
class Rope : cocos2d::CCDrawNode
{
public:
	Rope(cocos2d::Layer *layer);
	~Rope() {};
	
	Sprite* getRope();
	void setPosition(Vec2 pos);
	cocos2d::PhysicsBody* getRopePhysicsBody();

protected:
	cocos2d::Sprite *rope;
	cocos2d::Sprite *staticBody;
	cocos2d::PhysicsBody *RopePhysics;
	cocos2d::PhysicsBody *StaticRopePhysics;
};