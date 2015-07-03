#pragma once
#include "cocos2d.h"
#include "Definitions.h"
class Player
{
public:
	Player(cocos2d::Layer *layer);
	
	void runAction(cocos2d::Action *act);
	cocos2d::Vec2 getPosition();
	void Grapple(cocos2d::Vec2 touchPosition);

	void update();
	bool isHooked;
	bool isTouchHold;
	float power;

	cocos2d::Vec2 TouchPosition;
	cocos2d::PhysicsBody* getPlayerPhysicsBody();
	cocos2d::Sprite *getPlayer();
protected:
	cocos2d::Sprite* player;
	cocos2d::PhysicsBody *PlayerPhysics;
	
};

