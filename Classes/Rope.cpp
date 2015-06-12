#include "Rope.h"

using namespace cocos2d;

Rope::Rope()
{
	Lrope = CCDrawNode::create();
	fromPosition = Vec2(50, 50);
	toPosition = Vec2(100, 100);
	radius = 15;
}

Rope::~Rope()
{
}

CCDrawNode *Rope::getNode()
{
	return Lrope;
}

void Rope::setFromPosition(Vec2 pos)
{
	fromPosition = pos;
}

void Rope::setToPosition(Vec2 pos)
{
	toPosition = pos;
}

void Rope::setRadius(float r)
{
	radius = r;
}

Vec2 Rope::getFromPosition()
{

	return fromPosition;
}

Vec2 Rope::getToPosition()
{
	return toPosition;
}

float Rope::getRadius()
{
	return radius;
}