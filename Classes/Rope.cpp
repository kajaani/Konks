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
	RopePhysics->setVelocityLimit(1000);
	rope->setPhysicsBody(RopePhysics);

	// Another rope. nope.
	StaticRopePhysics = PhysicsBody::createCircle(10);
	StaticRopePhysics->setDynamic(false);
	staticBody = Sprite::create();
	staticBody->setPhysicsBody(StaticRopePhysics);


	rope->getPhysicsBody()->setContactTestBitmask(BITMASK_A);
	rope->getPhysicsBody()->setCategoryBitmask(BITMASK_B);

	layer->addChild(staticBody);
	layer->addChild(rope, 16);
}

Rope::~Rope()
{
	
}

void Rope::Grapple(Vec2 TouchPosition)
{
	if (rope->getPositionY() < TouchPosition.y)
		RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x, RopePhysics->getVelocity().y + 1000));

	if (rope->getPositionY() > TouchPosition.y)
		RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x, RopePhysics->getVelocity().y - 1000));

	if (rope->getPositionX() < TouchPosition.x)
		RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x + 1000, RopePhysics->getVelocity().y));

	if (rope->getPositionX() > TouchPosition.x)
		RopePhysics->setVelocity(Vec2(RopePhysics->getVelocity().x - 1000, RopePhysics->getVelocity().y));
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

float Rope::getRadius()
{
	return radius;
}