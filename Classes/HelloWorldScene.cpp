#include "HelloWorldScene.h"
#include "Tower.h"
#include "Waypoint.h"
#include "Enemy.h"

using namespace std;


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
	wave = 1;

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

	// 5 - Add enemies
	enemies = new CCArray();
	this->loadWave();

	// 6 - Create wave label
	ui_wave_lbl = CCLabelBMFont::create(CCString::createWithFormat("WAVE: %d", wave)->getCString(), "font_red_14.fnt");
	this->addChild(ui_wave_lbl ,10);
	ui_wave_lbl->setPosition(ccp(400, winSize.height - 12));
	ui_wave_lbl->setAnchorPoint(ccp(0, 0.5));

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


BOOL HelloWorld::circle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo)
{
	float xdif = circlePoint.x - circlePointTwo.x;
	float ydif = circlePoint.y - circlePointTwo.y;

	float distance = sqrt(xdif*xdif + ydif*ydif);

	if (distance <= radius + radiusTwo)
		return YES;

	return NO;
}

void HelloWorld::ccFillPoly(CCPoint* poli, int points, BOOL closePolygon)
{

}

void HelloWorld::getHpDamage()
{

}

BOOL HelloWorld::loadWave() 
{

	CCDictionary* waveData = CCDictionary::createWithContentsOfFile("Waves2.plist");
	if (wave >= 3)
	{
		return NO;
	}
	
	//CCDictionary* wave1 = (CCDictionary*)waveData->objectForKey("wave1");

	bool vaweToggle = true;
	CCDictElement* target = NULL;
	int c = 1;
	CCDICT_FOREACH(waveData, target)
	{
		if (c == 6) return YES;
		if (vaweToggle)
		{
			vaweToggle = false;
		}
		else{
			const CCString* pVal = waveData->valueForKey(target->getStrKey());
			Enemy* enemy = Enemy::createWithTheGame(this);
			enemies->addObject(enemy);
			enemy->schedule(schedule_selector(Enemy::doActivate),std::stof(pVal->getCString()));
			vaweToggle = true;
			c++;
		}
	}
	wave++;
	ui_wave_lbl->setString(CCString::createWithFormat("WAVE: %d", wave)->getCString());

	return YES;
}

void HelloWorld::enemyGotKilled()
{
	if (enemies->count() <= 0) //If there are no more enemies.
	{
		if (!this->loadWave())
		{
			CCLog("You win!");			
			CCDirector::sharedDirector()->replaceScene(CCTransitionSplitCols::create(1, HelloWorld::scene()));
		}
	}
}
