#include "CubeTest.h"

using namespace cocos2d;

CubeTest::CubeTest()
{
	LabelCubeTest = Label::create("", "fonts/Marker Felt.ttf", 32);
}

CubeTest::~CubeTest()
{
}

Label *CubeTest::getLabel()
{
	return LabelCubeTest;
}