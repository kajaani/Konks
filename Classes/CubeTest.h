#pragma once
#include "cocos2d.h"

class CubeTest : cocos2d::Label
{
public:
	CubeTest();
	~CubeTest();
	
	cocos2d::Label* getLabel();

protected:
	cocos2d::Label* LabelCubeTest;
};

