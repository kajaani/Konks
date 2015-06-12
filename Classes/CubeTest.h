#pragma once
#include "cocos2d.h"

class CubeTest : cocos2d::LabelTTF
{
public:
	CubeTest();
	~CubeTest();
	
	cocos2d::LabelTTF* getLabel();

protected:
	cocos2d::LabelTTF* LabelCubeTest;
};

