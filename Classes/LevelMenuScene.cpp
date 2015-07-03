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
	//Level 1 button
	playButton1 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToGameScene, this));
	playButton1->setName("Testmap9000.tmx");
	playButton1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + 100));

	//Level 2 button
	playButton2 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToGameScene, this));
	playButton2->setName("tutorial.tmx");
	playButton2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2));

	//Level 3 button
	playButton3 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToGameScene, this));
	playButton3->setName("Background03.tmx");
	playButton3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 100));
	
	//In addition to previous sprites the play button changes its graphics once clicked
	auto backButton = MenuItemImage::create("backButton.png", "backButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToMainMenuScene, this));
	backButton->setPosition(Point(visibleSize.width - 30, 30));

	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create(backButton, NULL);
	menu->setPosition(Point::ZERO); // == 0,
	menu->addChild(playButton1);
	menu->addChild(playButton2);
	menu->addChild(playButton3);
	this->addChild(menu);

	return true;
}

//Method that replaces the current scene with the game scene
void LevelMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto node = Node::create();
	node->setTag(50);

	if (sender->_ID == playButton1->_ID)
	{
		node->setName(playButton1->getName().c_str());
	}
	if (sender->_ID == playButton2->_ID)
	{
		node->setName(playButton2->getName().c_str());
	}
	if (sender->_ID == playButton3->_ID)
	{
		node->setName(playButton3->getName().c_str());
	}

	//CCLOG("%s", selectedLevel->getName().c_str());

	auto scene = HelloWorld::createScene();
	scene->addChild(node);

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//Method that replaces current scene with the main menu scene
void LevelMenuScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}