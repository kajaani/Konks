#include "Player.h"

using namespace cocos2d;

Player::Player(Layer *layer)
{
	power = 0;
	isTouchHold = false;
	isHooked = false;
	TouchPosition = Vec2(0, 0);

	player = Sprite::create("defpappa.png");
	player->setPosition(100, 120);
	player->setScale(0.5f);

	PlayerPhysics = PhysicsBody::createCircle(player->getContentSize().width / 6, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	PlayerPhysics->setVelocityLimit(500);

	PlayerPhysics->setGravityEnable(true);
	PlayerPhysics->setMass(1000);
	PlayerPhysics->setRotationEnable(false);

	PlayerPhysics->setCategoryBitmask(BITMASKPLAYER);
	PlayerPhysics->setCollisionBitmask(BITMASKTILE);
	PlayerPhysics->setContactTestBitmask(BITMASKCOLLISIONBOX);
	
	PlayerPhysics->setTag(12);

	player->setPhysicsBody(PlayerPhysics);
	layer->addChild(player, 15);
}

void Player::runAction(Action *act)
{
	player->runAction(act);
}

void Player::update()
{
	float distance = sqrt((player->getPositionX() - TouchPosition.x) * (player->getPositionX() - TouchPosition.x) + (player->getPositionY() - TouchPosition.y) * (player->getPositionY() - TouchPosition.y));

	if (isTouchHold && isHooked)
		power = 5;
	else if (!isTouchHold)
		power = 0;

	if (distance > 25 && isTouchHold && isHooked)
	{
		//

		// Use this to move player towards hook
		//float Dx = player->getPosition().x - touchWorld.x;
		//float Dy = player->getPosition().y - touchWorld.y;

		//float Dlength = sqrt(Dx*Dx + Dy*Dy);

		//Dx /= Dlength;
		//Dy /= Dlength;

		//

		// Player movement while hooked
		/*if (player->getPositionY() < TouchPosition.y)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y + power));

		if (player->getPositionY() > TouchPosition.y)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y - power));

		if (player->getPositionX() < TouchPosition.x)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x + power, PlayerPhysics->getVelocity().y));

		if (player->getPositionX() > TouchPosition.x)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x - power, PlayerPhysics->getVelocity().y));*/
	}

	//CCLOG("Velocity X: %f Y: %f", PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y);

	//if (isTouchHold)
	//	log("holding touch onn");
	//else
	//	log("holding touch off");
}


PhysicsBody* Player::getPlayerPhysicsBody()
{
	return PlayerPhysics;
}

cocos2d::Sprite* Player::getPlayer()
{
	return player;
}
void Player::Grapple(Vec2 touchPosition)
{
	TouchPosition = touchPosition;
	float distance = sqrt((player->getPositionX() - touchPosition.x) * (player->getPositionX() - touchPosition.x) + (player->getPositionY() - touchPosition.y) * (player->getPositionY() - touchPosition.y));
}

Vec2 Player::getPosition()
{
	return player->getPosition();
}