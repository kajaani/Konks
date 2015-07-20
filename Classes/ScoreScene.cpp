#include "ScoreScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "Constant.h"

USING_NS_CC;
float Constant::score = 0.0f;
Scene* ScoreScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = ScoreScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//Initializing and setting a value to the backgroundSprite
	auto backgroundSprite = Sprite::create("Background.png");
	//Setting the position of the backgroundSprite
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//Adding backgroundSprite to the MainMenuScene
	this->addChild(backgroundSprite);

	//Doing the same to the rest of the sprites
	auto titleSprite = Sprite::create("logo.png");
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height));
	this->addChild(titleSprite);
	
	//Printing highscore to the screen
	auto highscoreLabel = LabelTTF::create("", "fonts/arial.ttf", 24);
	highscoreLabel->setPosition(100, 100);

	UserDefault *def = UserDefault::getInstance();
	_highscore = def->getIntegerForKey(Constant::mapname.c_str(), 0);

	String *highscore = String::createWithFormat("Highscore: %.2f", _highscore);
	highscoreLabel->setString(highscore->getCString());

	this->addChild(highscoreLabel, 99);

	//Printing the latest score to the screen
	auto scoreLabel = LabelTTF::create("", "font/arial.ttf", 24);
	scoreLabel->setPosition(100, 150);

	//Constant::score retrieves the value from Constant.h
	_score = Constant::score;

	String *score = String::createWithFormat("Score: %.2f", _score);
	scoreLabel->setString(score->getCString());
	
	this->addChild(scoreLabel, 99);

	//Level 2 button
	menuButton = MenuItemImage::create("menuButton.png", "menuButton.png", CC_CALLBACK_1(
		ScoreScene::GoToMainMenuScene, this));
	menuButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2));

	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO); // == 0,
	menu->addChild(menuButton);
	this->addChild(menu);

	return true;
}

//Method that replaces current scene with the main menu scene
void ScoreScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}