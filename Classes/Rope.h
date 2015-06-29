#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Rope : cocos2d::CCDrawNode
{
public:
	Rope(cocos2d::Layer *layer);
	~Rope();
	
	cocos2d::CCDrawNode* getNode();
	
	Vec2 getRopePosition();
	Vec2 getToPosition();
	Sprite* getRope();

	void updateStaticBody(Vec2 pos);
	void setToPosition(Vec2 pos);
	void setRadius(float r);

	cocos2d::PhysicsBody* getRopePhysicsBody();
	cocos2d::PhysicsBody* getStaticRopePhysicsBody();

	void Grapple(Vec2 TouchPosition);
private:
	Vec2 fromPosition;
	Vec2 toPosition;
	float radius;

protected:
	cocos2d::Sprite *rope;
	cocos2d::Sprite *staticBody;
	cocos2d::PhysicsBody *RopePhysics;
	cocos2d::PhysicsBody *StaticRopePhysics;
};