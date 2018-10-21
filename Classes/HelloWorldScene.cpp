#include "HelloWorldScene.h"
#include <sstream>
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


	// 1 - Initialize
	this->setTouchEnabled(true);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 2 - Set background        
	CCSprite * background = CCSprite::create("bg.png");
	this->addChild(background);
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	// 3 - Load tower positions
	this->loadTowerPositions();

    return true;
}


void HelloWorld::loadTowerPositions()
{
	CCDictionary* towerPositions = CCDictionary::createWithContentsOfFile("TowersPosition.plist");
	CCArray* towerBases = CCArray::createWithCapacity(10);

	bool coordToggle = true;
	int x, y;

	CCDictElement* target = NULL;
	CCDICT_FOREACH(towerPositions, target)
	{
		const CCString* pVal = towerPositions->valueForKey(target->getStrKey());

		if (coordToggle)
		{
			
			x = std::stoi( pVal->getCString());
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

