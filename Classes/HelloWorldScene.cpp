#include "HelloWorldScene.h"
#include "math\CCMath.h"

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

void HelloWorld::setLevel( Scene* scene)
{
	CCLOG("adasdasdfgsdgsgsgsd %s", scene->getChildByTag(50)->getName().c_str());
	tile = new Peli::Tile(this, scene->getChildByTag(50)->getName().c_str());
}


// on "init" you need to initialize your instance
bool HelloWorld::init(PhysicsWorld* world)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
	
	// Following view
	this->runAction(Follow::create(player->getPlayer(),
		Rect(visibleSize.width  + origin.x - visibleSize.width, 
		visibleSize.height  + origin.y - visibleSize.height, 
		visibleSize.width * 100, 
		visibleSize.height * 100)));
    return true;
}

void HelloWorld::update(float dt)
{
	player->update();
	player->getPosition();
	LabelCubeTest->setColor(ccc3(rand() % 255, 0, 0));
	LabelCubeTest->setPosition(LabelCubeTest->getPositionX(), LabelCubeTest->getPositionY()-0.2);	
	LabelCubeTest->setRotation(LabelCubeTest->getRotation() + 1);
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
	Point touchWorld = convertToNodeSpace(touch->getLocation());

	float distance = sqrt((player->getPosition().x - touchWorld.x + movedDistance) * (player->getPosition().x - touchWorld.x + movedDistance) +
		(player->getPosition().y - touchWorld.y) * (player->getPosition().y - touchWorld.y));

	ropeJoint = PhysicsJointLimit::construct(player->getPlayerPhysicsBody(), rope->getRopePhysicsBody(), Point::ZERO, Point::ZERO, 50.0f, distance - 25);
	_world->addJoint(ropeJoint);

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
	player->Grapple(Vec2(touchWorld.x + movedDistance, touchWorld.y));

	//rope->setToPosition(Vec2(touch->getLocation().x + (this->getScene()->getDefaultCamera()->getPosition().x/2), touch->getLocation().y)); // Add something to touch coordinates
	rope->setToPosition(Vec2(touchWorld.x + movedDistance, touchWorld.y)); // Add something to touch coordinates

	//CCLOG("Camera position: %f, %f", this->getScene()->getDefaultCamera()->getPosition().x, this->getScene()->getDefaultCamera()->getPosition().y);
	//CCLOG("Touch position: %f, %f", touch->getLocation().x, touch->getLocation().y);

	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	_world->removeJoint(ropeJoint);
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
