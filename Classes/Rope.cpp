#include "Rope.h"

using namespace cocos2d;

Rope::Rope(cocos2d::Layer *layer)
{
	rope = Sprite::create("CloseSelected.png");
	rope->setPosition(Vec2(600, 600));
	fromPosition = Vec2(50, 50);
	toPosition = Vec2(100, 100);
	radius = 15;

	int BITMASK_A = 0x1;
	int BITMASK_B = 0x2;

	RopePhysics = PhysicsBody::createCircle(10);
	RopePhysics->setDynamic(true); 
	RopePhysics->setEnable(true);
	RopePhysics->setGravityEnable(false);
	RopePhysics->setVelocityLimit(1000);
	rope->setPhysicsBody(RopePhysics);
	rope->setName("ropename");
	// Another rope. nope.
	/*StaticRopePhysics = PhysicsBody::createCircle(10);
	StaticRopePhysics->setDynamic(false);*/
	/*staticBody = Sprite::create();
	staticBody->setPhysicsBody(StaticRopePhysics);*/
	
	rope->getPhysicsBody()->setContactTestBitmask(BITMASK_B);
	rope->getPhysicsBody()->setCategoryBitmask(BITMASK_A);

	/*staticBody->getPhysicsBody()->setContactTestBitmask(BITMASK_B);
	staticBody->getPhysicsBody()->setCategoryBitmask(BITMASK_A);*/
	
	rope->getPhysicsBody()->setTag(13);
	//staticBody->getPhysicsBody()->setTag(13);

	//layer->addChild(staticBody, 17);
	layer->addChild(rope, 16);
}

Rope::~Rope()
{
	
}

void Rope::Grapple(Vec2 TouchPosition)
{
	rope->stopAllActions();
	//if (rope->getPositionY() < TouchPosition.y)
	//	RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x, RopePhysics->getVelocity().y + 1000));

	//if (rope->getPositionY() > TouchPosition.y)
	//	RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x, RopePhysics->getVelocity().y - 1000));

	//if (rope->getPositionX() < TouchPosition.x)
	//	RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x + 1000, RopePhysics->getVelocity().y));

	//if (rope->getPositionX() > TouchPosition.x)
	//	RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x - 1000, RopePhysics->getVelocity().y));
	rope->runAction(MoveTo::create(1, TouchPosition));
}

PhysicsBody* Rope::getRopePhysicsBody()
{
	return RopePhysics;
}
PhysicsBody* Rope::getStaticRopePhysicsBody()
{
	return StaticRopePhysics;
}
void Rope::updateStaticBody(Vec2 pos)
{
	staticBody->setPosition(pos);
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

Vec2 Rope::getRopePosition()
{
	return rope->getPosition();
}

Vec2 Rope::getToPosition()
{
	return toPosition;
}

Sprite* Rope::getRope()
{
	return rope;
}