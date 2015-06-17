#include "SettingsScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SettingsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//Initializing variables which help with the placement of elements
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Slider example
	auto slider = cocos2d::ui::Slider::create();
	slider->setPercent(50);
	slider->loadBarTexture("Slider_Empty.png"); // what the slider looks like
	slider->loadSlidBallTextures("SliderButton_Normal.png", "SliderButton_Pressed.png", "SliderButton_Disabled.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");
	slider->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); // Where the slider will be positioned
	
	//Listening to the changes of the state of the slider
	slider->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
		switch (type)
		{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				log("Slider moved");
				break;
			default:
				break;
		}
	});

	this->addChild(slider); // Adding the slider to the scene

	//In addition to previous sprites the play button changes its graphics once clicked
	auto backButton = MenuItemImage::create("backButton.png", "backButtonClicked.png", CC_CALLBACK_1(
		SettingsScene::GoToMainMenuScene, this));
	backButton->setPosition(Point(visibleSize.width - 30, 30));
	

	//Initializing the menu, placing the buttons and setting it visible
	auto menu = Menu::create(backButton, NULL);
	menu->setPosition(Point::ZERO); // == 0,
	this->addChild(menu);
	

	return true;
}

//Method that replaces current scene with the main menu scene
void SettingsScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}