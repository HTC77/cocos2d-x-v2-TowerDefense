#ifndef __TowerDefense__Enemy__
#define __TowerDefense__Enemy__

#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Waypoint.h"

USING_NS_CC;

class Enemy : public CCNode
{
public:
	Enemy();
	~Enemy();
	static Enemy* create();
	bool init();
	
	CCPoint myPosition;
	int maxHp;
	int currentHp;
	float walkingSpeed;
	Waypoint* destinationWaypoint;
	BOOL active;

	HelloWorld* theGame;
	CCSprite *mySprite;
	static Enemy* createWithTheGame(HelloWorld* _game);
	bool initWithTheGame(HelloWorld* _game);

	void doActivate(float dt);
	void getRemoved();
	void draw();
	void update(float dt);
};

#endif

