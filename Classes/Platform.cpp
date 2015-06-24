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

void Platform::spawnPlatform(Layer *layer, Vec2 playerPosition)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto platform = Sprite::create("platform.png");
	platform->setPosition(Vec2(visibleSize.width + playerPosition.x + rand() % 100, playerPosition.y - visibleSize.height + rand() % 600));

	auto platformPhysics = PhysicsBody::createBox(platform->getContentSize());

	platformPhysics->setGravityEnable(false);
	platformPhysics->setDynamic(false);
	platformPhysics->setEnable(true);
	platformPhysics->setMass(10000);

	platform->setPhysicsBody(platformPhysics);

	auto moveTo = MoveTo::create(9, Vec2(playerPosition.x - 800 + rand() % 100, platform->getPositionY()));
	platform->runAction(moveTo);
	
	layer->addChild(platform);
}