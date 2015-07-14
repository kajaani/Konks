#include "Player.h"

using namespace cocos2d;

Player::Player(Layer *layer)
{
	power = 0;
	isTouchHold = false;
	isHooked = false;
	TouchPosition = Vec2(0, 0);

	player = Sprite::create("Fleng/character_animation_fleng00 copy.png");
	player->setPosition(100, 1120);
	//player->setScale(0.1f);

	PlayerPhysics = PhysicsBody::createCircle(player->getContentSize().width * 0.5, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	PlayerPhysics->setVelocityLimit(500);

	PlayerPhysics->setGravityEnable(true);
	PlayerPhysics->setMass(1000);
	PlayerPhysics->setRotationEnable(false);

	PlayerPhysics->setCategoryBitmask(BITMASKPLAYER);
	PlayerPhysics->setCollisionBitmask(BITMASKTILE);
	PlayerPhysics->setContactTestBitmask(BITMASKCOLLISIONBOX);
	
	PlayerPhysics->setTag(PLAYER);

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
		power = 10;
	else if (!isTouchHold)
	{
		player->stopAllActions();
		power = 0;

		if (player->getRotation() > 10)
		{
			player->setRotation(player->getRotation() - 10);
		}
	}

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
		if (player->getPositionY() < TouchPosition.y)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y ));

		if (player->getPositionY() > TouchPosition.y)
			PlayerPhysics->setVelocity(Vec2(PlayerPhysics->getVelocity().x, PlayerPhysics->getVelocity().y ));

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

void Player::Fleng()
{	
	Vector<SpriteFrame*> animFrames(15);

	char str[100] = { 0 };
	for (int i = 0; i <= 14; i++)
	{
		//character_animation100.png // run00%0d.png
		sprintf(str, "Fleng/character_animation_fleng0%i copy.png", i);
		frame = SpriteFrame::create(str, Rect(0, 0, 100, 100));
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	if (isTouchHold)
	{
		animation->setLoops(-1);
	}
	
	animate = Animate::create(animation);
	player->runAction(animate);
}

void Player::Shoot()
{
	Vector<SpriteFrame*> animFrames(20);

	char str[100] = { 0 };
	for (int i = 100; i <= 119; i++)
	{
		//character_animation100.png // run00%0d.png
		sprintf(str, "Fleng/character_throw_air100 copy.png", i);
		frame = SpriteFrame::create(str, Rect(0, 0, 100, 100));
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05f);

	animate = Animate::create(animation);
	player->runAction(animate);
}