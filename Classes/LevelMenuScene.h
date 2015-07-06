#ifndef __LEVEL_MENU_SCENE_H__
#define __LEVEL_MENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
class LevelMenuScene : public cocos2d::Layer
{
public:
	std::string _selectedLevel;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(LevelMenuScene);

private:
	cocos2d::MenuItemImage* playButton1;
	cocos2d::MenuItemImage* playButton2;
	cocos2d::MenuItemImage* playButton3;
	void GoToGameScene(cocos2d::Ref *sender);
	void GoToMainMenuScene(cocos2d::Ref *sender);

};

#endif // __LEVEL_MENU_SCENE_H__