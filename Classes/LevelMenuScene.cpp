#include "LevelMenuScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "Constant.h"

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
	if (!Layer::init())
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

	UserDefault *def = UserDefault::getInstance();

	//In addition to previous sprites the play button changes its graphics once clicked

	Constant::attempts = 0;

	//Level 1 button
		playButton1 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
			LevelMenuScene::GoToGameScene, this));
		playButton1->setName("Maps/First.tmx");
		auto label1 = Label::create("", "fonts/Marker Felt.ttf", 32);

		float _highscore = def->getIntegerForKey(playButton1->getName().c_str(), 0);
		std::string shortName = playButton1->getName().erase(0, 5);
		shortName.erase(shortName.length() - 4, 4);

		String *text1 = String::createWithFormat("%s: \n%.2f", shortName.c_str(), _highscore);
		label1->setString(text1->getCString());
		CCLOG("Level Select Score: %f", _highscore);

		playButton1->setPosition(Point(0, visibleSize.height));
		playButton1->setAnchorPoint(Vec2(0, 1));
		label1->setPosition(Vec2(playButton1->getPosition().x + label1->getContentSize().width / 2, playButton1->getPosition().y - label1->getContentSize().height / 2));

	//Level 2 button
		playButton2 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
			LevelMenuScene::GoToGameScene, this));
		playButton2->setName("Maps/Second.tmx");
		auto label2 = Label::create(playButton2->getName().c_str(), "fonts/Marker Felt.ttf", 32);

		float _highscore2 = def->getIntegerForKey(playButton2->getName().c_str(), 0);
		std::string shortName2 = playButton2->getName().erase(0, 5);
		shortName2.erase(shortName2.length() - 4, 4);

		String *text2 = String::createWithFormat("%s: \n%.2f", shortName2.c_str(), _highscore2);
		label2->setString(text2->getCString());
		CCLOG("Level Select Score: %f", _highscore2);
	
		playButton2->setPosition(Vec2(playButton1->getPosition().x + playButton1->getContentSize().width, playButton1->getPosition().y));
		playButton2->setAnchorPoint(Vec2(0, 1));
		label2->setPosition(Vec2(playButton2->getPosition().x + label2->getContentSize().width / 2, playButton2->getPosition().y - label2->getContentSize().height / 2));

	//Level 3 button
		playButton3 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
			LevelMenuScene::GoToGameScene, this));
		playButton3->setName("Maps/Third.tmx");
		auto label3 = Label::create(playButton3->getName().c_str(), "fonts/Marker Felt.ttf", 32);

		float _highscore3 = def->getIntegerForKey(playButton3->getName().c_str(), 0);
		std::string shortName3 = playButton3->getName().erase(0, 5);
		shortName3.erase(shortName3.length() - 4, 4);

		String *text3 = String::createWithFormat("%s: \n%.2f", shortName3.c_str(), _highscore3);
		label3->setString(text3->getCString());
		CCLOG("Level Select Score: %f", _highscore3);

		playButton3->setPosition(Vec2(playButton2->getPosition().x + playButton3->getContentSize().width, playButton2->getPosition().y));
		playButton3->setAnchorPoint(Vec2(0, 1));
		label3->setPosition(Vec2(playButton3->getPosition().x + label3->getContentSize().width / 2, playButton3->getPosition().y - label3->getContentSize().height / 2));

	//Level 4 button
		playButton4 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
			LevelMenuScene::GoToGameScene, this));
		playButton4->setName("Maps/Fourth.tmx");
		auto label4 = Label::create(playButton4->getName().c_str(), "fonts/Marker Felt.ttf", 32);

		float _highscore4 = def->getIntegerForKey(playButton4->getName().c_str(), 0);
		std::string shortName4 = playButton4->getName().erase(0, 5);
		shortName4.erase(shortName4.length() - 4, 4);

		String *text4 = String::createWithFormat("%s: \n%.2f", shortName4.c_str(), _highscore4);
		label4->setString(text4->getCString());
		CCLOG("Level Select Score: %f", _highscore4);

		playButton4->setPosition(Vec2(playButton3->getPosition().x + playButton4->getContentSize().width, playButton3->getPosition().y));
		playButton4->setAnchorPoint(Vec2(0, 1));
		label4->setPosition(Vec2(playButton4->getPosition().x + label4->getContentSize().width / 2, playButton4->getPosition().y - label4->getContentSize().height / 2));

	//Level 5 button
		playButton5 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
			LevelMenuScene::GoToGameScene, this));
		playButton5->setName("Maps/Fifth.tmx");
		auto label5 = Label::create(playButton5->getName().c_str(), "fonts/Marker Felt.ttf", 32);

		float _highscore5 = def->getIntegerForKey(playButton5->getName().c_str(), 0);
		std::string shortName5 = playButton5->getName().erase(0, 5);
		shortName5.erase(shortName5.length() - 4, 4);

		String *text5 = String::createWithFormat("%s: \n%.2f", shortName5.c_str(), _highscore5);
		label5->setString(text5->getCString());
		CCLOG("Level Select Score: %f", _highscore5);

		playButton5->setPosition(Vec2(playButton1->getPosition().x, playButton1->getPosition().y - playButton5->getContentSize().height));
		playButton5->setAnchorPoint(Vec2(0, 1));
		label5->setPosition(Vec2(playButton5->getPosition().x + label5->getContentSize().width / 2, playButton5->getPosition().y - label5->getContentSize().height / 2));

	//Level 6 button
		playButton6 = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_1(
			LevelMenuScene::GoToGameScene, this));
		playButton6->setName("Maps/Sixth.tmx");
		auto label6 = Label::create(playButton6->getName().c_str(), "fonts/Marker Felt.ttf", 32);

		float _highscore6 = def->getIntegerForKey(playButton6->getName().c_str(), 0);
		std::string shortName6 = playButton6->getName().erase(0, 5);
		shortName6.erase(shortName6.length() - 4, 4);

		String *text6 = String::createWithFormat("%s: \n%.2f", shortName6.c_str(), _highscore6);
		label6->setString(text6->getCString());
		CCLOG("Level Select Score: %f", _highscore6);

		playButton6->setPosition(Vec2(playButton5->getPosition().x + playButton6->getContentSize().width, playButton5->getPosition().y));
		playButton6->setAnchorPoint(Vec2(0, 1));
		label6->setPosition(Vec2(playButton6->getPosition().x + label6->getContentSize().width / 2, playButton6->getPosition().y - label6->getContentSize().height / 2));

	// Confirm
	confirmButton = MenuItemImage::create("CloseNormal.png", "PlayButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::ConfirmLevel, this));
	confirmButton->setPosition(100, 100);

	//In addition to previous sprites the play button changes its graphics once clicked
	auto backButton = MenuItemImage::create("backButton.png", "backButtonClicked.png", CC_CALLBACK_1(
		LevelMenuScene::GoToMainMenuScene, this));
	backButton->setPosition(Point(visibleSize.width - 30, 30));

	//Initializing the menu, placing the buttons and setting it visible
	menu = Menu::create(backButton, NULL);
	menu->setPosition(Point::ZERO); // == 0,
	menu->addChild(playButton1);
	menu->addChild(playButton2);
	menu->addChild(playButton3);
	menu->addChild(playButton4);
	menu->addChild(playButton5);
	menu->addChild(playButton6);

	menu->addChild(confirmButton);

	this->addChild(label1, 1);
	this->addChild(label2, 1);
	this->addChild(label3, 1);
	this->addChild(label4, 1);
	this->addChild(label5, 1);
	this->addChild(label6, 1);

	this->addChild(menu);

	return true;
}

//Method that replaces the current scene with the game scene
void LevelMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	if (sender->_ID == playButton1->_ID)
	{
		Constant::mapname = playButton1->getName().c_str();
	}
	if (sender->_ID == playButton2->_ID)
	{
		Constant::mapname = playButton2->getName().c_str();
	}
	if (sender->_ID == playButton3->_ID)
	{
		Constant::mapname = playButton3->getName().c_str();
	}
	if (sender->_ID == playButton4->_ID)
	{
		Constant::mapname = playButton4->getName().c_str();
	}
	if (sender->_ID == playButton5->_ID)
	{
		Constant::mapname = playButton5->getName().c_str();
	}
	if (sender->_ID == playButton6->_ID)
	{
		Constant::mapname = playButton6->getName().c_str();
	}
}

void LevelMenuScene::ConfirmLevel(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//Method that replaces current scene with the main menu scene
void LevelMenuScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}