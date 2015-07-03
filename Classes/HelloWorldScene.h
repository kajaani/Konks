#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Tile.h"
#include "Box2D\Box2D.h"
#include "CubeTest.h"
#include "Player.h"
#include "Rope.h"
#include "Platform.h"

class HelloWorld : public cocos2d::Layer
{
public:

	void setLevel(Scene *scene);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	//static cocos2d::Scene* createScene(std::string level);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);
	void initializeLevel(float dt);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onContactPostSolve(cocos2d::PhysicsContact &contact, const cocos2d::PhysicsContactPostSolve &solve);

	void SpawnPlatform(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

protected:
	CubeTest* cube;
	cocos2d::LabelTTF* LabelCubeTest;

	Rope *rope;
	Player *player;
	Platform platform;

	Peli::Tile *tile;

	// Physics
	cocos2d::PhysicsJointLimit *ropeJoint;
	cocos2d::PhysicsWorld *_world;
	cocos2d::Node *node;

	std::string _selectedLevel;

	bool isAlreadyRoped;
	float distance;
	float distanceFromHook;
	float oldRopePosX = 0;
	Point origin;
	Size visibleSize;
	Vec2 boxHitPos;

	DrawNode *_drawNode;
	Sprite *sprite;

private:
	void GoToMainMenuScene(cocos2d::Ref *sender);

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _world = world; };

};

#endif // __HELLOWORLD_SCENE_H__