#include "CubeTest.h"

using namespace cocos2d;

CubeTest::CubeTest()
{
	LabelCubeTest = LabelTTF::create("", "fonts/Marker Felt.ttf", 72);
}

CubeTest::~CubeTest()
{
}

LabelTTF *CubeTest::getLabel()
{
	return LabelCubeTest;
}