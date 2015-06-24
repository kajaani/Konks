#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Tile.h"
#include "Box2D\Box2D.h"
#include "CubeTest.h"
#include "Player.h"
#include "Rope.h"
#include "Platform.h"

#define CUSTOM_CREATE_FUNC(__TYPE__) \
static __TYPE__* create(PhysicsWorld* world) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(world)) \
	    { \
       pRet->autorelease(); \
       return pRet; \
	     } \
	      else \
	      { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
	        } \
}

class HelloWorld : public cocos2d::Layer
{
public:

	void setLevel( Scene *scene);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	//static cocos2d::Scene* createScene(std::string level);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(PhysicsWorld* world);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);
	void initializeLevel(float dt);
	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void SpawnPlatform(float dt); 
	
    // implement the "static create()" method manually
	CUSTOM_CREATE_FUNC(HelloWorld);

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

	float movedDistance = 0;
	Point origin;
	Size visibleSize;

private:
	void GoToMainMenuScene(cocos2d::Ref *sender);

};

#endif // __HELLOWORLD_SCENE_H__