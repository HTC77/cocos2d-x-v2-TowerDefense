#ifndef __TowerDefense__Tower__
#define __TowerDefense__Tower__

#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Enemy.h"

USING_NS_CC;

#define kTOWER_COST 300
class Enemy;
class Tower : public CCNode
{
public:
	Tower();
	~Tower();
	static Tower* create();
	bool init();
	int attackRange;
	int damage;
	float fireRate;
	HelloWorld* theGame;
	CCSprite* mySprite;

	static Tower* createWithTheGame(HelloWorld* _game, CCPoint location);
	bool initWithTheGame(HelloWorld* _game ,CCPoint location);

	void update(float dt);
	void draw();

	BOOL attacking;
	Enemy* chosenEnemy;
	void targetKilled();
	
	void attackEnemy();
	void shootWeapon(float dt);
	void chosenEnemyForAttack(Enemy* enemy);
	void removeBullet(CCSprite* bullet);
	void damageEnemy();
	void lostSightOfEnemy();
};

#endif

