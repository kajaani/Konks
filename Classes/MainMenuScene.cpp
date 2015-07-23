#include "MainMenuScene.h"
#include "GameScene.h"
#include "LevelMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"  
#include "Constant.h"

USING_NS_CC;

bool Constant::soundMuted = false;
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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//Initializing and setting a value to the backgroundSprite
	auto backgroundSprite = Sprite::create("mainmenu_bg.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScale(1);
	this->addChild(backgroundSprite);

	//In addition to previous sprites the play button changes its graphics once clicked
	auto playButton = MenuItemImage::create("PlayButton.png", "PlayButton.png", CC_CALLBACK_1(
		MainMenuScene::GoToGameScene, this));
	playButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	//Settings button initialization and placement 
	auto levelsButton = MenuItemImage::create("levelsButton.png", "levelsButton.png", CC_CALLBACK_1(
		MainMenuScene::GoToLevelMenuScene, this));
	levelsButton->setPosition(Point(playButton->getPosition().x, playButton->getPosition().y - playButton->getContentSize().height * 1.15));

	//Doing the same to the rest of the sprites
	auto titleSprite = Sprite::create("logo.png");
	titleSprite->setPosition(Point(playButton->getPosition().x, playButton->getPosition().y + playButton->getContentSize().height * 1.25));
	this->addChild(titleSprite);
	
	muteButton = MenuItemImage::create("soundEnabled.png", "soundEnabled.png", CC_CALLBACK_1(
		MainMenuScene::MuteSound, this));
	muteButton->setPosition(Point(50,50));

	muted = cocos2d::Sprite::create("soundDisabled.png");
	notMuted = cocos2d::Sprite::create("soundEnabled.png");

	if (Constant::soundMuted)
	{
		muteButton->setNormalImage(muted);
	}

	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create(playButton, NULL);
	menu->setPosition(Point::ZERO);
	menu->addChild(levelsButton);
	menu->addChild(muteButton);
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

void MainMenuScene::MuteSound(cocos2d::Ref *sender)
{
	muted = cocos2d::Sprite::create("soundDisabled.png");
	notMuted = cocos2d::Sprite::create("soundEnabled.png");
	
	//Muted -> not muted
	if (Constant::soundMuted)
	{
		muteButton->setNormalImage(notMuted);
		Constant::soundMuted = false;
	}
	//Not muted -> muted
	else
	{
		muteButton->setNormalImage(muted);
		Constant::soundMuted = true;
	}

	
}