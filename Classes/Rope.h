#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Rope : cocos2d::CCDrawNode
{
public:
	Rope(cocos2d::Layer *layer);
	~Rope();
	
	cocos2d::CCDrawNode* getNode();
	
	Vec2 getFromPosition();
	Vec2 getToPosition();
	float getRadius();

	void setFromPosition(Vec2 pos);
	void setToPosition(Vec2 pos);
	void setRadius(float r);

	cocos2d::PhysicsBody* getRopePhysicsBody();

private:
	Vec2 fromPosition;
	Vec2 toPosition;
	float radius;

protected:
	cocos2d::Sprite *rope;
	cocos2d::PhysicsBody *RopePhysics;
};