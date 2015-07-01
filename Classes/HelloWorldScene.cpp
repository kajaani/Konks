#include "HelloWorldScene.h"
#include "math\CCMath.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
	log("create scene");

	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void HelloWorld::setLevel(Scene* scene)
{
	tile = new Peli::Tile(this, scene->getChildByTag(50)->getName().c_str());

	this->runAction(Follow::create(player->getPlayer(),
		Rect(visibleSize.width + origin.x - visibleSize.width,
		visibleSize.height + origin.y - visibleSize.height,
		tile->getMap()->getMapSize().width * tile->getMap()->getTileSize().width,
		tile->getMap()->getMapSize().height * tile->getMap()->getTileSize().height)));

	//this->runAction(MoveTo::create(100, Vec2(-tile->getMap()->getMapSize().width * tile->getMap()->getTileSize().width, 0)));
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//log("initialize");

	if (!Layer::init())
	{
		return false;
	}

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
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Touch input
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	platform.spawnPlatform(this, player->getPosition());

	/////////////////////////////////////////////////////////////////////////////////////////////////
	scheduleOnce(schedule_selector(HelloWorld::initializeLevel), 0.1); // VERY HAZARD, PLEASE KILL ME
	/////////////////////////////////////////////////////////////////////////////////////////////////

	schedule(schedule_selector(HelloWorld::SpawnPlatform), 1.5);
	schedule(schedule_selector(HelloWorld::update));
	return true;
}

void HelloWorld::initializeLevel(float dt)
{
	setLevel(this->getScene());
}

void HelloWorld::SpawnPlatform(float dt)
{
	platform.spawnPlatform(this, player->getPosition());
}

void HelloWorld::update(float dt)
{
	player->update();
	player->getPosition();
	LabelCubeTest->setColor(ccc3(rand() % 255, 0, 0));
	LabelCubeTest->setPosition(LabelCubeTest->getPositionX(), LabelCubeTest->getPositionY() - 0.2);
	LabelCubeTest->setRotation(LabelCubeTest->getRotation() + 1);

	//Checks if the player is outside of the screen
	if (player->getPosition().x <= 0 || player->getPosition().y <= 0)
	{
		this->GoToMainMenuScene(this);
	}
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	float distanceFromHook;
	distanceFromHook = sqrt((player->getPosition().x - contact.getShapeA()->getBody()->getPosition().x + movedDistance) * (player->getPosition().x - contact.getShapeA()->getBody()->getPosition().x + movedDistance) +
		(player->getPosition().y - contact.getShapeA()->getBody()->getPosition().y) * (player->getPosition().y - contact.getShapeA()->getBody()->getPosition().y));
	
	// Player hits goal
	if (bodyA->getTag() == 12 && bodyB->getTag() == 12)
	{
		this->GoToMainMenuScene(this);
		return false;
	}
	if (bodyB->getTag() == 12 && bodyA->getTag() == 12)
	{
		this->GoToMainMenuScene(this);
	}

	// Hook hits player, cancel
	if (bodyA->getTag() == 12 && bodyB->getTag() == 13)
	{
		return false;
	}
	if (bodyB->getTag() == 12 && bodyA->getTag() == 13)
	{
		return false;
	}
	return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	// RayCast
	player->getPlayerPhysicsBody()->setEnable(true); // Disabled player collisions while testing raycast functioning //

	Point touchWorld = touch->getLocationInView();
	touchWorld = Director::sharedDirector()->convertToGL(touchWorld);
	touchWorld = this->convertToNodeSpace(touchWorld);

	Vec2 RayHitPosition(0, 0);
	bool isHit = false;
	
	////////////////////////////////////////////////
	player->getPlayerPhysicsBody()->setEnable(true);

	if (_drawNode)
	{
		removeChild(_drawNode);
	} 
	_drawNode = DrawNode::create();
	
	PhysicsRayCastCallbackFunc func = [&RayHitPosition, &isHit](PhysicsWorld& world,
		const PhysicsRayCastInfo& info, void* data)->bool
	{
		CCLOG("Raycasting");
		if (info.shape->getBody()->getTag() == 11)
		{
			isHit = true;
			RayHitPosition = info.contact;
			
			CCLOG("contact %f, %f", info.contact.x, info.contact.y);
			return false;
		}
		return true;
	};

	if (!RayHitPosition.x)
	{
		RayHitPosition = touchWorld;
		isHit = false;
	}

	//CCLOG("camera  %f, %f", this->getPosition().x, this->getPosition().y);
	//CCLOG("touch   %f, %f", touchWorld.x, touchWorld.y);
	
	this->getScene()->getPhysicsWorld()->rayCast(func, player->getPosition(), touchWorld, nullptr);
	_drawNode->drawSegment(player->getPosition(), touchWorld, 1, Color4F::RED);
	//_world->rayCast(func, player->getPosition(), touchWorld, nullptr);

	this->addChild(_drawNode);

	distance = sqrt((player->getPosition().x - RayHitPosition.x + movedDistance) * (player->getPosition().x - RayHitPosition.x + movedDistance) +
		(player->getPosition().y - RayHitPosition.y) * (player->getPosition().y - RayHitPosition.y));

	rope->getRopePhysicsBody()->setEnable(false);

	player->isTouchHold = true;
	Vector<SpriteFrame*> animFrames(46);

	char str[100] = { 0 };
	for (int i = 23; i < 46; i++)
	{
		sprintf(str, "PappaRun/run00%0d.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 254, 272));
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	player->runAction(animate);

	if (distance > 100 && player->isTouchHold && isHit)
	{
		rope->getRopePhysicsBody()->setDynamic(false);
		ropeJoint = PhysicsJointLimit::construct(player->getPlayerPhysicsBody(), rope->getRopePhysicsBody(), Point::ZERO, Point::ZERO, 50.0f, distance - 50);
		ropeJoint->setCollisionEnable(true);
		_world->addJoint(ropeJoint);

		auto distancefromvec1tovec2 = player->getPosition() - touchWorld;

		////////////////////////////////////////////////////////////////////////////////////////////
		//Determines the direction which player faces upon shooting the "hook"
		//CCLOG("Current angle: %f", CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle()));
		////////////////////////////////////////////////////////////////////////////////////////////

		if (((CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle())) > 90 && (CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle())) <= 179)
			|| ((CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle())) > -180 && (CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle())) <= -90))
		{
			//player->getPlayer()->setRotation(CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle()));
			player->getPlayer()->setScaleX(0.5);
		}
		else
		{
			player->getPlayer()->setScaleX(-0.5);
		}
		
		player->Grapple(touchWorld);
		rope->setToPosition(player->getPosition());
		rope->Grapple(RayHitPosition);
		player->isHooked = true;
	}
	return true;
}

void HelloWorld::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	rope->getRopePhysicsBody()->setDynamic(false);
	_world->removeAllJoints();
	player->isHooked = false;
	player->isTouchHold = false;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point touchWorld = convertToNodeSpace(touch->getLocation());
	player->TouchPosition = touchWorld;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

//float Dx = player->getPosition().x - touchWorld.x;
//float Dy = player->getPosition().y - touchWorld.y;

//float Dlength = sqrt(Dx*Dx + Dy*Dy);

//Dx /= Dlength;
//Dy /= Dlength;