#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Rope : cocos2d::CCDrawNode
{
public:
	Rope();
	~Rope();
	
	cocos2d::CCDrawNode* getNode();
	
	Vec2 getFromPosition();
	Vec2 getToPosition();
	float getRadius();

	void setFromPosition(Vec2 pos);
	void setToPosition(Vec2 pos);
	void setRadius(float r);

private:
	Vec2 fromPosition;
	Vec2 toPosition;
	float radius;

protected:
	cocos2d::CCDrawNode* Lrope;
};