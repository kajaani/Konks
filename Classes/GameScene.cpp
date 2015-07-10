#include "GameScene.h"
#include "math\CCMath.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "ScoreScene.h"
#include "Constant.h"

// TODO LIST //
/*
	Lag issues with android (camera or tiles?)
	Animations
	Final final final final final level design
	Fix bouncing between walls
	Save progress
	Sound effects
*/

USING_NS_CC;
#define COCOS2D_DEBUG 1
using namespace cocos2d;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameScene::setLevel(Scene* scene)
{
	tile = new Peli::Tile(this, scene->getChildByTag(MAPNAME)->getName().c_str());
	
	// Follow view
	this->runAction(Follow::create(player->getPlayer(),
		Rect(visibleSize.width + origin.x - visibleSize.width,
		visibleSize.height + origin.y - visibleSize.height,
		tile->getMap()->getMapSize().width * tile->getMap()->getTileSize().width,
		tile->getMap()->getMapSize().height * tile->getMap()->getTileSize().height)));

	// Scrolling view
	//this->runAction(cocos2d::MoveTo::create(50, Vec2(-tile->getMap()->getMapSize().width * tile->getMap()->getTileSize().width, this->getPosition().y)));

	float gravityMultiplier = 2;
	_world->setGravity(Vec2(0, -98 * gravityMultiplier));
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	if (!Layer::init())
	{
		return false;
	}

	isAlreadyRoped = false;
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	// Physics boundaries
	//auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	//edgeNode->setPhysicsBody(body);
	//this->addChild(edgeNode);

	// Text
	cube = new CubeTest();
	LabelCubeTest = cube->getLabel();
	LabelCubeTest->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - LabelCubeTest->getContentSize().height);

	// Player
	player = new Player(this);

	// Rope
	rope = new Rope(this);

	auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	// add the label as a child to this layer
	this->addChild(LabelCubeTest, 1);

	// Physics listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(GameScene::onContactPostSolve, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Touch input
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	platform.spawnPlatform(this, player->getPosition());


	sprite = Sprite::create("CloseSelected.png");
	sprite->setTag(RAYCASTCOLLISIONBOX);
	this->addChild(sprite);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	scheduleOnce(schedule_selector(GameScene::initializeLevel), 0.1); // VERY HAZARD, PLEASE KILL ME
	/////////////////////////////////////////////////////////////////////////////////////////////////

	schedule(schedule_selector(GameScene::SpawnPlatform), 1.5);
	schedule(schedule_selector(GameScene::update));
	schedule(schedule_selector(GameScene::TimerMilliSeconds), 0.1);

	auto highscorelabel = LabelTTF::create("", "fonts/arial.ttf", 72);
	highscorelabel->setPosition(100, 100);

	UserDefault *def = UserDefault::getInstance();
	highscore = def->getIntegerForKey("SCORE", 0);
	
	String *score = String::createWithFormat("Score: %.2f", highscore);
	highscorelabel->setString(score->getCString());

	this->addChild(highscorelabel, 99);
	//this->setKeypadEnabled(true);

	return true;
}

void GameScene::TimerMilliSeconds(float dt)
{
	// do stuph
	timeMilliseconds += 0.1;
}

void GameScene::update(float dt)
{
	Point hitWorld = convertToNodeSpace(boxHitPos);
	float realDistance = player->getPosition().distance(hitWorld);

	player->update();
	LabelCubeTest->setPosition(Vec2(-this->getPosition().x + LabelCubeTest->getContentSize().width / 2, -this->getPosition().y + visibleSize.height - LabelCubeTest->getContentSize().height / 2));
	LabelCubeTest->setColor(ccc3(255, 255, 0));
	String *score = String::createWithFormat("%.2f", timeMilliseconds);

	LabelCubeTest->setString(score->getCString());

	if (realDistance > 50 && player->isTouchHold && player->isHooked && !isAlreadyRoped)
	{
		rope->getRopePhysicsBody()->setEnable(false);
		rope->getRopePhysicsBody()->setDynamic(false);

		rope->setPosition(sprite->getPosition());

		ropeJoint = PhysicsJointLimit::construct(player->getPlayerPhysicsBody(), rope->getRopePhysicsBody(), Point::ZERO, Point::ZERO, 50.0f, realDistance - 50);
		ropeJoint->setCollisionEnable(true);

		_world->addJoint(ropeJoint);
		isAlreadyRoped = true;
	}
	
	if (realDistance > 50 && player->isTouchHold && player->isHooked && isAlreadyRoped)
	{
		// Pull player to hook here
	}

	//Checks if the player is outside of the screen
	if (player->getPosition().x <= 0 || player->getPosition().y <= 0)
	{
		this->GoToMainMenuScene(this);
	}

	// Hide hook if it doesnt hit the wall
	if (sprite && !player->isHooked && player->isTouchHold)
	{
		if (sprite->numberOfRunningActions() == 0)
			sprite->setPosition(Vec2(-1000,-1000));
	}

	if (_drawNode)
	{
		removeChild(_drawNode);
	}
	
	_drawNode = DrawNode::create();

	float rayCastOffset = 100;
	if (isAlreadyRoped)
	{
		Point ropeBodyA = player->getPlayer()->getPosition();
		Point ropeBodyB =rope->getRope()->getPosition();

		_drawNode->drawSegment(ropeBodyA, ropeBodyB, 1, Color4F::BLACK);
	}
	this->addChild(_drawNode);
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	this->GoToMainMenuScene(this);
}

void GameScene::onContactPostSolve(PhysicsContact &contact, const PhysicsContactPostSolve &solve)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag() == PLAYER && bodyB->getTag() == TILE)
	{
		bodyA->setVelocity(Vec2(bodyA->getVelocity().x * 0.99, bodyA->getVelocity().y * 0.99));
	}
	if (bodyB->getTag() == PLAYER && bodyA->getTag() == TILE)
	{
		bodyB->setVelocity(Vec2(bodyB->getVelocity().x * 0.99, bodyB->getVelocity().y * 0.99));
	}
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	
	distanceFromHook = player->getPosition().distance(contact.getShapeA()->getBody()->getPosition());

	
	if ((bodyA->getCategoryBitmask() & bodyB->getCollisionBitmask()) == 0
		|| (bodyB->getCategoryBitmask() & bodyA->getCollisionBitmask()) == 0)
	{
		// Player hits goal
		if (bodyA->getTag() == PLAYER && bodyB->getTag() == GOAL)
		{
			if (timeMilliseconds < highscore || highscore == 0)
			{
				UserDefault *def = UserDefault::getInstance();
				highscore = timeMilliseconds;
				def->setIntegerForKey("SCORE", highscore);
			}
			this->GoToScoreScene(this);
			return false;
		}
		if (bodyB->getTag() == PLAYER && bodyA->getTag() == GOAL)
		{
			this->GoToScoreScene(this);
			return false;
		}

		// Hook hits player, cancel
		if (bodyA->getTag() == PLAYER && bodyB->getTag() == HOOK)
		{
			return false;
		}
		if (bodyB->getTag() == PLAYER && bodyA->getTag() == HOOK)
		{
			return false;
		}

		// RayBox hits player
		if (bodyA->getTag() == PLAYER && bodyB->getTag() == RAYCASTCOLLISIONBOX)
		{
			return false;
		}
		if (bodyB->getTag() == PLAYER && bodyA->getTag() == RAYCASTCOLLISIONBOX)
		{
			return false;
		}
		if (sprite)
		{
			// RayBox hits tiles
			if (player->isTouchHold)
			{
				if (bodyA->getTag() == RAYCASTCOLLISIONBOX && bodyB->getTag() == TILE)
				{
					sprite->stopAllActions();
					boxHitPos = bodyA->getPosition();
					player->Run();
					player->isHooked = true;
					return true;
				}
				else if (bodyB->getTag() == RAYCASTCOLLISIONBOX && bodyA->getTag() == TILE)
				{
					sprite->stopAllActions();
					boxHitPos = bodyA->getPosition();
					player->isHooked = true;
					player->Run();
					return true;
				}
			}
		}
	}

	return true;
}

void GameScene::initializeLevel(float dt)
{
	setLevel(this->getScene());
}

void GameScene::SpawnPlatform(float dt)
{
	//platform.spawnPlatform(this, player->getPosition());
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point touchWorld = convertToNodeSpace(touch->getLocation());
	player->isTouchHold = true;
	if (sprite)
	{
		removeChild(sprite);
	}

	sprite = Sprite::create("CloseSelected.png");
	sprite->setColor(ccc3(100, 0, 0));
	sprite->setPosition(player->getPosition());

	auto spriteBody = PhysicsBody::createBox(sprite->getContentSize() * 0.8);
	sprite->setPhysicsBody(spriteBody);

	sprite->getPhysicsBody()->setCategoryBitmask(BITMASKCOLLISIONBOX);
	sprite->getPhysicsBody()->setCollisionBitmask(BITMASKNONE);
	sprite->getPhysicsBody()->setContactTestBitmask(BITMASKTILE);

	sprite->getPhysicsBody()->setGravityEnable(false);
	sprite->getPhysicsBody()->setDynamic(true);
	sprite->getPhysicsBody()->setTag(RAYCASTCOLLISIONBOX);

	this->addChild(sprite);
	 
	sprite->runAction(MoveTo::create(0.25, touchWorld));

	// RayCast
	player->getPlayerPhysicsBody()->setEnable(true); // Disabled player collisions while testing raycast functioning //
	Vec2 points;
	Vec2 RayHitPosition(0, 0);
	int num = 0;

	player->Shoot();

	distance = sqrt((player->getPosition().x - boxHitPos.x) * (player->getPosition().x - boxHitPos.x) +
		(player->getPosition().y - boxHitPos.y) * (player->getPosition().y - boxHitPos.y));

	if (distance > 50 && player->isTouchHold)
	{			
		//Handling the rotation of the player, depending on where he shoots

		Point fromplayertohook = ccpSub(player->getPosition(), touchWorld);
		float angle = -CC_RADIANS_TO_DEGREES(ccpToAngle(fromplayertohook));
		float realangle = angle + 270;

		sprite->setRotation(realangle);

		if ((angle > 90 && angle <= 179) || (angle > -180 && angle <= -90))
		{
	
			player->getPlayer()->setScaleX(0.5);
		}
		else
		{
			player->getPlayer()->setScaleX(-0.5);
		}
		player->Grapple(Vec2(touchWorld.x, touchWorld.y));
	}
	return true;
}

void GameScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameScene::GoToScoreScene(cocos2d::Ref *sender)
{
	auto scene = ScoreScene::createScene();

	Constant::score = timeMilliseconds;

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	rope->getRopePhysicsBody()->setDynamic(false);
	_world->removeAllJoints();
	player->isHooked = false;
	player->isTouchHold = false;
	isAlreadyRoped = false;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point touchWorld = convertToNodeSpace(touch->getLocation());
	player->TouchPosition = Vec2(touchWorld.x, touchWorld.y);
}

void GameScene::Pause()
{
	Director::getInstance()->pause();
	//player->getPlayerPhysicsBody()->setResting(true);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
