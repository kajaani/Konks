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
	auto layer = HelloWorld::create(scene->getPhysicsWorld());
	//layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}

void HelloWorld::setLevel(Scene* scene)
{
	CCLOG("adasdasdfgsdgsgsgsd %s", scene->getChildByTag(50)->getName().c_str());
	tile = new Peli::Tile(this, scene->getChildByTag(50)->getName().c_str());
	this->runAction(Follow::create(player->getPlayer(),
		Rect(visibleSize.width + origin.x - visibleSize.width,
		visibleSize.height + origin.y - visibleSize.height,
		tile->getMap()->getMapSize().width * tile->getMap()->getTileSize().width,
		tile->getMap()->getMapSize().height * tile->getMap()->getTileSize().height)));
}


// on "init" you need to initialize your instance
bool HelloWorld::init(PhysicsWorld* world)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	log("initialize");
	_world = world;
	Vect g = _world->getGravity();
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
	//

	// Player
	player = new Player(this);

	// Rope
	rope = new Rope(this);

	auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	// add the label as a child to this layer
	this->addChild(LabelCubeTest, 1);

	// add "HelloWorld" splash screen"
	auto background = Sprite::create("Desert.jpg");

	// position the sprite on the center of the screen
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	//this->addChild(background, 0);

	// Physics listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(HelloWorld::onContactPostSolve, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Touch input
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	//

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
	//rope->updateStaticBody(rope->getRopePosition());
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


void HelloWorld::onContactPostSolve(PhysicsContact &contact)
{
	//auto bodyA = contact.getShapeA()->getBody();
	//auto bodyB = contact.getShapeB()->getBody();
	//log("Nigga stole my bike");
	//if (bodyA->getTag() == 13 && bodyB->getTag() == 11)
	//{
	//	_world->removeBody(rope->getRopePhysicsBody());
	//}
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

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	// RayCast
	player->getPlayerPhysicsBody()->setEnable(true); // Disabled player collisions while testing raycast functioning //
	Point touchWorld = convertToNodeSpace(touch->getLocation());

	CCLOG("  Touch   position    at: %f, %f", touchWorld.x, touchWorld.y);
	Vec2 points[5];
	Vec2 RayHitPosition(0, 0);
	int num = 0;
	bool isHit = false;


	if (_drawNode)
	{
		removeChild(_drawNode);
	}
	_drawNode = DrawNode::create();

	PhysicsRayCastCallbackFunc func = [&points, &num, &RayHitPosition, &isHit](PhysicsWorld& world,
		const PhysicsRayCastInfo& info, void* data)->bool
	{
		if (num < 5)
		{
			isHit = true;
			points[num++] = info.contact;
			RayHitPosition = points[0];
			CCLOG("RayCast hit something at: %f, %f", info.contact.x, info.contact.y);
		}
		return true;
	};

	if (!RayHitPosition.x)
	{
		RayHitPosition = touchWorld;
		isHit = false;
	}

	float Dx = player->getPosition().x - touchWorld.x;
	float Dy = player->getPosition().y - touchWorld.y;

	float Dlength = sqrt(Dx*Dx + Dy*Dy);

	Dx /= Dlength;
	Dy /= Dlength;

	_world->rayCast(func, Vec2(player->getPosition().x + Dx * -100, player->getPosition().y + Dy * -100), touchWorld, nullptr);
	_drawNode->drawSegment(Vec2(player->getPosition().x + Dx * -100, player->getPosition().y + Dy * -100), touchWorld, 1, Color4F::RED);
	this->addChild(_drawNode);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	distance = sqrt((player->getPosition().x - RayHitPosition.x + movedDistance) * (player->getPosition().x - RayHitPosition.x + movedDistance) +
		(player->getPosition().y - RayHitPosition.y) * (player->getPosition().y - RayHitPosition.y));

	///////////////////////////////////////////
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

		player->Grapple(Vec2(touchWorld.x + movedDistance, touchWorld.y));
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
	player->TouchPosition = Vec2(touchWorld.x + movedDistance, touchWorld.y);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
