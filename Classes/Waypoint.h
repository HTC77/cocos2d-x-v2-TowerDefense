#ifndef __TowerDefense__Waypoint__
#define __TowerDefense__Waypoint__

#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;

class Waypoint : public CCNode
{
public:
	Waypoint();
	~Waypoint();
	static Waypoint* create();
	bool init();
	HelloWorld* theGame;
	CCPoint myPosition;
	Waypoint* nextWaypoint;

	static Waypoint* createWithTheGame(HelloWorld* _game, CCPoint location);
	bool initWithTheGame(HelloWorld* _game, CCPoint location);
	virtual void draw();
};

#endif

