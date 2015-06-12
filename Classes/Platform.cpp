#include "Platform.h"

using namespace cocos2d;

Platform::Platform()
{
	position = Vec2(0, 0);
}


void Platform::setPosition(Vec2 newPos)
{
	position = newPos;
}

void Platform::spawnPlatform(Layer *layer)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("Spawning");

	auto platform = Sprite::create("platform.png");
	platform->setPosition(Vec2(visibleSize.width + rand() % 100, rand() % 600));

	auto platformPhysics = PhysicsBody::createBox(platform->getContentSize());

	platformPhysics->setGravityEnable(false);
	platformPhysics->setDynamic(false);
	platformPhysics->setEnable(false);
	platformPhysics->setMass(10000);

	platform->setPhysicsBody(platformPhysics);

	auto moveTo = MoveTo::create(6, Vec2(-400, platform->getPositionY()));
	platform->runAction(moveTo);
	
	layer->addChild(platform);
}