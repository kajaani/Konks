#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
class ScoreScene : public cocos2d::Layer
{
public:
	std::string _selectedLevel;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(ScoreScene);

private:
	cocos2d::MenuItemImage* continueButton;
	cocos2d::MenuItemImage* menuButton;
	cocos2d::MenuItemImage* quitButton;
	void GoToGameScene(cocos2d::Ref *sender);
	void GoToMainMenuScene(cocos2d::Ref *sender);
	void Quit(cocos2d::Ref *sender);

	float _score;
	float _highscore;
};

#endif // __SCORE_SCENE_H__