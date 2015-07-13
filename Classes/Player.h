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

	//Animations
	void Fleng();
	void Shoot();

	void update();
	bool isHooked;
	bool isTouchHold;
	float power;

	cocos2d::Vec2 TouchPosition;
	cocos2d::PhysicsBody* getPlayerPhysicsBody();
	cocos2d::Sprite *getPlayer();
private:
	cocos2d::Animation *animation;
	cocos2d::Animate *animate;
	cocos2d::Vector<cocos2d::SpriteFrame*> *animFrames;
	cocos2d::SpriteFrame *frame;
protected:
	cocos2d::Sprite* player;
	cocos2d::PhysicsBody *PlayerPhysics;
	
};

