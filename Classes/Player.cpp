#include "Player.h"

using namespace cocos2d;

Player::Player(Layer *layer)
{
	power = 0;
	isTouchHold = false;
	isHooked = false;
	TouchPosition = Vec2(0, 0);

	player = Sprite::create("defpappa.png");
	player->setPosition(Vec2(250, 250));

	PlayerPhysics = PhysicsBody::createBox(Size(112, 219));
	PlayerPhysics->setVelocityLimit(2000);

	PlayerPhysics->setGravityEnable(true);
	PlayerPhysics->setMass(1000);

	PlayerPhysics->setRotationEnable(false);

	player->setPhysicsBody(PlayerPhysics);

	layer->addChild(player, 15);	
}

void Player::runAction(Action *act)
{
	PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x , PlayerPhysics->getVelocity().y + 200));
	player->runAction(act);
}

void Player::update()
{
		//PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x + 2.5, PlayerPhysics->getVelocity().y - 5));
		float distance = sqrt((player->getPositionX() - TouchPosition.x) * (player->getPositionX() - TouchPosition.x) + (player->getPositionY() - TouchPosition.y) * (player->getPositionY() - TouchPosition.y));

		if (isTouchHold)
			power = 5;
		else if (!isTouchHold)
			power = 0;

		if (distance > 25 && isTouchHold)
		{
			if (player->getPositionY() < TouchPosition.y)
				PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y + power));

			if (player->getPositionY() > TouchPosition.y)
				PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y - power));

			if (player->getPositionX() < TouchPosition.x)
				PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x + power, PlayerPhysics->getVelocity().y));

			if (player->getPositionX() > TouchPosition.x)
				PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x - power, PlayerPhysics->getVelocity().y));
		}



		//CCLOG("Velocity X: %f Y: %f", PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y);

		//if (isTouchHold)
		//	log("holding touch onn");
		//else
		//	log("holding touch off");
}

void Player::Grapple(Vec2 touchPosition)
{
	TouchPosition = touchPosition;
	float distance = sqrt((player->getPositionX() - touchPosition.x) * (player->getPositionX() - touchPosition.x) + (player->getPositionY() - touchPosition.y) * (player->getPositionY() - touchPosition.y));
	CCLOG("Distance %f", distance);

	auto jump = JumpTo::create(3, Vec2(TouchPosition), distance, 1);
	

	/*if (player->getPositionY() < touchPosition.y)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x , PlayerPhysics->getVelocity().y + distance));

	if (player->getPositionY() > touchPosition.y)
		PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x , -PlayerPhysics->getVelocity().y - distance));

	if (player->getPositionX() < touchPosition.x)
		PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x + distance, PlayerPhysics->getVelocity().y ));

	if (player->getPositionX() > touchPosition.x)
		PlayerPhysics->setVelocity(Vec2(-PlayerPhysics->getVelocity().x - distance, PlayerPhysics->getVelocity().y ));*/
}

Vec2 Player::getPosition()
{
	return player->getPosition();
}