#include "LevelMenuScene.h"

#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* LevelMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LevelMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelMenuScene::init()
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
	playButton = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToGameScene, this, playButton));
	playButton->setName("Background02.tmx");
	playButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + 100));

	//In addition to previous sprites the play button changes its graphics once clicked
	auto backButton = MenuItemImage::create("backButton.png", "backButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToMainMenuScene, this));
	backButton->setPosition(Point(visibleSize.width - 30, 30));

	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create(backButton, NULL);
	menu->setPosition(Point::ZERO); // == 0,
	menu->addChild(playButton);
	this->addChild(menu);

	return true;
}

//Method that replaces the current scene with the game scene
void LevelMenuScene::GoToGameScene(cocos2d::Ref *sender, cocos2d::MenuItemImage *selectedLevel)
{
	//CCLOG("Level name: %s", playButton->getName().c_str());

	_selectedLevel = playButton->getName(); //selectedLevel->getName().c_str();
	CCLOG("Nappia painettu, %s", _selectedLevel.c_str());
	//CCLOG("%s", selectedLevel->getName().c_str());

	auto scene = HelloWorld::createScene();
	
	auto node = Node::create();
	node->setName(playButton->getName().c_str());
	node->setTag(50);
	scene->addChild(node);

	CCLOG("Level name in levelmenuscene: %s", scene->getChildByTag(50)->getName().c_str());

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//Method that replaces current scene with the main menu scene
void LevelMenuScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}