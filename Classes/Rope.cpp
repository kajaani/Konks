#include "Rope.h"

using namespace cocos2d;

Rope::Rope(cocos2d::Layer *layer)
{
	rope = Sprite::create("CloseSelected.png");
	rope->setPosition(Vec2(600, 600));
	fromPosition = Vec2(50, 50);
	toPosition = Vec2(100, 100);
	radius = 15;

	int BITMASK_A = 0x1 << 0;
	int BITMASK_B = 0x1 << 1;

	RopePhysics = PhysicsBody::createCircle(10);
	RopePhysics->setDynamic(true); 
	RopePhysics->setEnable(true);
	RopePhysics->setTag(11);
	rope->setPhysicsBody(RopePhysics);

	rope->getPhysicsBody()->setContactTestBitmask(BITMASK_A);
	rope->getPhysicsBody()->setCategoryBitmask(BITMASK_B);

	layer->addChild(rope, 16);
}

Rope::~Rope()
{
	
}

PhysicsBody* Rope::getRopePhysicsBody()
{
	return RopePhysics;
}

void Rope::setFromPosition(Vec2 pos)
{
	fromPosition = pos;
}

void Rope::setToPosition(Vec2 pos)
{
	toPosition = pos;
	rope->setPosition(pos);
}

void Rope::setRadius(float r)
{
	radius = r;
}

Vec2 Rope::getFromPosition()
{

	return fromPosition;
}

Vec2 Rope::getToPosition()
{
	return toPosition;
}

float Rope::getRadius()
{
	return radius;
}