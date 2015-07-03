#include "Rope.h"

using namespace cocos2d;

Rope::Rope(cocos2d::Layer *layer)
{
	rope = Sprite::create();
	rope->setPosition(Vec2(600, 600));

	RopePhysics = PhysicsBody::createCircle(10);
	RopePhysics->setDynamic(true); 
	RopePhysics->setEnable(true);
	RopePhysics->setGravityEnable(false);
	RopePhysics->setVelocityLimit(1000);
	rope->setPhysicsBody(RopePhysics);
	rope->setName("ropename");
	
	rope->getPhysicsBody()->setCategoryBitmask(BITMASKROPE);
	rope->getPhysicsBody()->setCollisionBitmask(BITMASKNONE);
	rope->getPhysicsBody()->setContactTestBitmask(BITMASKNONE);
	
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