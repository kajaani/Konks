#include "HelloWorldScene.h"
#include "math\CCMath.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_JOINT);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void HelloWorld::setLevel(Scene* scene)
{
	//CCLOG("adasdasdfgsdgsgsgsd %s", scene->getChildByTag(50)->getName().c_str());
	tile = new Peli::Tile(this, scene->getChildByTag(50)->getName().c_str());
	this->runAction(Follow::create(player->getPlayer(),
		Rect(visibleSize.width + origin.x - visibleSize.width,
		visibleSize.height + origin.y - visibleSize.height,
		tile->getMap()->getMapSize().width * tile->getMap()->getTileSize().width,
		tile->getMap()->getMapSize().height * tile->getMap()->getTileSize().height)));

	float gravityMultiplier = 2;
	_world->setGravity(Vec2(0, -98 * gravityMultiplier));
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

void HelloWorld::update(float dt)
{
	player->update();
	player->getPosition();
	LabelCubeTest->setColor(ccc3(rand() % 255, 0, 0));
	LabelCubeTest->setPosition(LabelCubeTest->getPositionX(), LabelCubeTest->getPositionY() - 0.2);
	LabelCubeTest->setRotation(LabelCubeTest->getRotation() + 1);

	Point hitWorld = convertToNodeSpace(boxHitPos);
	float realDistance = player->getPosition().distance(hitWorld);

	if (realDistance > 50 && player->isTouchHold && player->isHooked && !isAlreadyRoped)
	{
		log("PlayerPos: %f, %f", player->getPosition().x, player->getPosition().y);
		log("hit box  : %f, %f", boxHitPos.x, boxHitPos.y);
		
		log("Distance 1: %f", realDistance);
		log("Distance 2: %f", distanceFromHook);

		isAlreadyRoped = true;
		rope->getRopePhysicsBody()->setEnable(false);
		rope->getRopePhysicsBody()->setDynamic(false);

		rope->setPosition(sprite->getPosition());

		ropeJoint = PhysicsJointLimit::construct(player->getPlayerPhysicsBody(), rope->getRopePhysicsBody(), Point::ZERO, Point::ZERO, 50.0f, realDistance - 50);
		ropeJoint->setCollisionEnable(true);

		_world->addJoint(ropeJoint);
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
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	//distanceFromHook = sqrt((player->getPosition().x - contact.getShapeA()->getBody()->getPosition().x ) * (player->getPosition().x - contact.getShapeA()->getBody()->getPosition().x ) +
	//	(player->getPosition().y - contact.getShapeA()->getBody()->getPosition().y) * (player->getPosition().y - contact.getShapeA()->getBody()->getPosition().y));

	distanceFromHook = player->getPosition().distance(contact.getShapeA()->getBody()->getPosition());

	// Player hits goal
	if (bodyA->getTag() == 12 && bodyB->getTag() == 12)
	{
		CCLOG("BODY A OSUI");
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
		log("hook hit player");
		return false;
	}
	if (bodyB->getTag() == 12 && bodyA->getTag() == 13)
	{
		log("hook hit player");
		return false;
	}

	// RayBox hits player
	if (bodyA->getTag() == 12 && bodyB->getTag() == 22)
	{
		//CCLOG("BOX OSUI PELAAJAAN");
		return false;
	}
	if (bodyB->getTag() == 12 && bodyA->getTag() == 22)
	{
		//CCLOG("BOX OSUI PELAAJAAN");
		return false;
	}

	// RayBox hits tiles
	if (bodyA->getTag() == 22 && bodyB->getTag() == 11)
	{
		sprite->stopAllActions();
		boxHitPos = bodyA->getPosition();
		player->isHooked = true;
		return true;
	}
	if (bodyB->getTag() == 22 && bodyA->getTag() == 11)
	{
		sprite->stopAllActions();
		boxHitPos = bodyA->getPosition();
		player->isHooked = true;
		return true;
	}
	return true;
}

void HelloWorld::initializeLevel(float dt)
{
	setLevel(this->getScene());
}

void HelloWorld::SpawnPlatform(float dt)
{
	//platform.spawnPlatform(this, player->getPosition());
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point touchWorld = convertToNodeSpace(touch->getLocation());
	player->isTouchHold = true;
	if (sprite)
	{
		removeChild(sprite);
	}

	sprite = Sprite::create("skull.jpg");
	sprite->setScale(0.2);
	sprite->setColor(ccc3(100, 0, 0));
	sprite->setPosition(player->getPosition());

	auto spriteBody = PhysicsBody::createBox(sprite->getContentSize() * 0.2);
	sprite->setPhysicsBody(spriteBody);

	int BITMASK_A = 0x1;
	int BITMASK_B = 0x2;

	sprite->getPhysicsBody()->setContactTestBitmask(BITMASK_B);
	sprite->getPhysicsBody()->setCategoryBitmask(BITMASK_A);
	sprite->getPhysicsBody()->setGravityEnable(false);
	sprite->getPhysicsBody()->setDynamic(true);
	sprite->getPhysicsBody()->setTag(22);

	this->addChild(sprite);

	sprite->runAction(MoveTo::create(0.25, touchWorld));

	// RayCast
	player->getPlayerPhysicsBody()->setEnable(true); // Disabled player collisions while testing raycast functioning //
	Vec2 points;
	Vec2 RayHitPosition(0, 0);
	int num = 0;

	if (_drawNode)
	{
		removeChild(_drawNode);
	}
	_drawNode = DrawNode::create();

	float rayCastOffset = 100;
	_drawNode->drawSegment(Vec2(player->getPosition().x, player->getPosition().y), touchWorld, 1, Color4F::RED);
	this->addChild(_drawNode);

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

	distance = sqrt((player->getPosition().x - boxHitPos.x) * (player->getPosition().x - boxHitPos.x) +
		(player->getPosition().y - boxHitPos.y) * (player->getPosition().y - boxHitPos.y));

	if (distance > 50 && player->isTouchHold)
	{	
		//Handling the rotation of the player, depending on where he shoots
		auto distancefromvec1tovec2 = player->getPosition() - touchWorld;

		float angle = (CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle()));

		if ((angle > 90 && angle <= 179) || (angle > -180 && angle <= -90))
		{
			//player->getPlayer()->setRotation(CC_RADIANS_TO_DEGREES(distancefromvec1tovec2.getAngle()));
			player->getPlayer()->setScaleX(0.5);
		}
		else
		{
			player->getPlayer()->setScaleX(-0.5);
		}
		player->Grapple(Vec2(touchWorld.x + movedDistance, touchWorld.y));
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
	isAlreadyRoped = false;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point touchWorld = convertToNodeSpace(touch->getLocation());
	player->TouchPosition = Vec2(touchWorld.x + movedDistance, touchWorld.y);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
