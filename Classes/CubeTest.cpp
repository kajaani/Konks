#include "CubeTest.h"

using namespace cocos2d;

CubeTest::CubeTest()
{
	LabelCubeTest = LabelTTF::create("Hello World", "fonts/NextGames.ttf", 72);
}

CubeTest::~CubeTest()
{
}

LabelTTF *CubeTest::getLabel()
{
	return LabelCubeTest;
}