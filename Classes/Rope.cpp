#include "Rope.h"

using namespace cocos2d;

Rope::Rope(cocos2d::Layer *layer)
{
	rope = Sprite::create("CloseSelected.png");
	rope->setPosition(Vec2(600, 600));
	
	int BITMASK_A = 0x1;
	int BITMASK_B = 0x2;

	RopePhysics = PhysicsBody::createCircle(10);
	RopePhysics->setDynamic(true); 
	RopePhysics->setEnable(true);
	RopePhysics->setGravityEnable(false);
	RopePhysics->setVelocityLimit(1000);
	rope->setPhysicsBody(RopePhysics);
	rope->setName("ropename");
	
	rope->getPhysicsBody()->setContactTestBitmask(BITMASK_B);
	rope->getPhysicsBody()->setCategoryBitmask(BITMASK_A);
	
	rope->getPhysicsBody()->setTag(13);

	layer->addChild(rope, 16);
}

PhysicsBody* Rope::getRopePhysicsBody()
{
	return RopePhysics;
}

void Rope::setPosition(Vec2 pos)
{
	rope->setPosition(pos);
}

Sprite* Rope::getRope()
{
	return rope;
}