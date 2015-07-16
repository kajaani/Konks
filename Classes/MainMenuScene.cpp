#include "MainMenuScene.h"
#include "GameScene.h"
#include "LevelMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
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
	auto backgroundSprite = Sprite::create("Muumilaakso.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScale(4);
	this->addChild(backgroundSprite);

	//Doing the same to the rest of the sprites
	auto titleSprite = Sprite::create("logo.png");
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height));
	this->addChild(titleSprite);

	//In addition to previous sprites the play button changes its graphics once clicked
	auto playButton = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
		MainMenuScene::GoToGameScene, this));
	playButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + 100));

	//Quit button initialization and placement
	auto quitButton = MenuItemImage::create("QuitButton.png", "QuitButtonClicked.png", CC_CALLBACK_1(
		MainMenuScene::Quit, this));
	quitButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 100));

	//Settings button initialization and placement 
	auto levelsButton = MenuItemImage::create("levelsButton.png", "levelsButtonClicked.png", CC_CALLBACK_1(
		MainMenuScene::GoToLevelMenuScene, this));
	levelsButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2));
	
	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create(playButton, NULL);
	menu->setPosition(Point::ZERO);
	menu->addChild(levelsButton);
	menu->addChild(quitButton);
	this->addChild(menu);

	return true;
}

//Method which replaces the current scene with the game scene
void MainMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto node = Node::create();
	node->setTag(MAPNAME);
	node->setName("Hugemap.tmx");

	auto scene = GameScene::createScene();
	scene->addChild(node);

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


//Method which replaces the current scene with the level menu scene
void MainMenuScene::GoToLevelMenuScene(cocos2d::Ref *sender)
{
	auto scene = LevelMenuScene::createScene();
	
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//Quits the game
void MainMenuScene::Quit(cocos2d::Ref *sender)
{
	exit(0);
}