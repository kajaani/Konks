#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "LevelMenuScene.h"
#include "SettingsScene.h"
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
	auto backgroundSprite = Sprite::create("Background.png");
	//Setting the position of the backgroundSprite
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//Adding backgroundSprite to the MainMenuScene
	this->addChild(backgroundSprite);

	//Doing the same to the rest of the sprites
	auto titleSprite = Sprite::create("Title.png");
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
	levelsButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 5));

	//Settings button initialization and placement 
	auto settingsButton = MenuItemImage::create("SettingsButton.png", "SettingsButtonClicked.png", CC_CALLBACK_1(
		MainMenuScene::GoToSettingsScene, this));
	settingsButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2));
	
	// Sound on/off toggle
	/*CCMenuItem *soundOnItem = [CCMenuItemImage item: @"soundOn.png"
							selectedImage:@"soundOn.png"
								   target:nil
								 selector:nil];
 
	CCMenuItem *soundOffItem = [CCMenuItemImage itemFromNormalImage:@"soundOff.png"
							 selectedImage:@"soundOff.png"
								target:nil
								  selector:nil];
 
	CCMenuItemToggle *soundToggleItem = [CCMenuItemToggle itemWithTarget:self
									selector:@selector(soundButtonTapped:)
									   items:soundOnItem, soundOffItem, nil];*/


	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create(playButton, NULL);
	menu->setPosition(Point::ZERO);
	menu->addChild(settingsButton);
	menu->addChild(levelsButton);
	menu->addChild(quitButton);
	this->addChild(menu);

	return true;
}

//Method which replaces the current scene with the game scene
void MainMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto node = Node::create();
	node->setTag(50);
	node->setName("Background01.tmx");

	auto scene = HelloWorld::createScene();
	scene->addChild(node);

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//Method which replaces the current scene with the settings scene
void MainMenuScene::GoToSettingsScene(cocos2d::Ref *sender)
{
	auto scene = SettingsScene::createScene();

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