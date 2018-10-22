#include "HelloWorldScene.h"
#include "Tower.h"
#include "Waypoint.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	towerBases = new CCArray(12);
	towers = new CCArray();

	// 1 - Initialize
	this->setTouchEnabled(true);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 2 - Set background        
	CCSprite * background = CCSprite::create("bg.png");
	this->addChild(background);
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	// 3 - Load tower positions
	this->loadTowerPositions();

	// 4 - Add waypoints
	this->addWaypoints();

    return true;
}


void HelloWorld::loadTowerPositions()
{
	CCDictionary* towerPositions = CCDictionary::createWithContentsOfFile("TowersPosition.plist");

	bool coordToggle = true;
	int x, y;

	CCDictElement* target = NULL;
	CCDICT_FOREACH(towerPositions, target)
	{
		const CCString* pVal = towerPositions->valueForKey(target->getStrKey());

		if (coordToggle)
		{
			
			x = std::stoi(pVal->getCString());
			coordToggle = false;
		}
		else
		{
			y = std::stoi(pVal->getCString());
			CCSprite* towerBase = CCSprite::create("open_spot.png");
			towerBase->setPosition(ccp(x,y));
			this->addChild(towerBase);
			towerBases->addObject(towerBase);
			coordToggle = true;
		}
	}
}


BOOL HelloWorld::canBuyTower()
{
	return true;
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCObject* t = NULL;
	CCARRAY_FOREACH(towerBases,t)
	{
		CCSprite* tb = (CCSprite*) t;
		if (tb->boundingBox().containsPoint(location) && this->canBuyTower() && !tb->getUserData())
		{
			//We will spend our gold later.

			Tower * tower = Tower::createWithTheGame(this, tb->getPosition());
			towers->addObject(tower);
			tb->setUserData(tower);
		}
	}
}


void HelloWorld::addWaypoints()
{
	waypoints = new CCArray();

	Waypoint * waypoint1 = Waypoint::createWithTheGame (this,ccp(420, 35));
	waypoints->addObject(waypoint1);

	Waypoint * waypoint2 = Waypoint::createWithTheGame (this,ccp(35, 35));
	waypoints->addObject(waypoint2);
	waypoint2->nextWaypoint = waypoint1;

	Waypoint * waypoint3 = Waypoint::createWithTheGame (this,ccp(35, 130));
	waypoints->addObject(waypoint3);
	waypoint3->nextWaypoint = waypoint2;

	Waypoint * waypoint4 = Waypoint::createWithTheGame (this,ccp(445, 130));
	waypoints->addObject(waypoint4);
	waypoint4->nextWaypoint = waypoint3;

	Waypoint * waypoint5 = Waypoint::createWithTheGame (this,ccp(445, 220));
	waypoints->addObject(waypoint5);
	waypoint5->nextWaypoint = waypoint4;

	Waypoint * waypoint6 = Waypoint::createWithTheGame (this,ccp(-40, 220));
	waypoints->addObject(waypoint6);
	waypoint6->nextWaypoint = waypoint5;
}
