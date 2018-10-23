#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define YES TRUE
#define NO FALSE

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	CCArray* towerBases;
	void loadTowerPositions();
	CCArray* towers;

	BOOL canBuyTower();
	void ccTouchesBegan(CCSet* pTouches, CCEvent* event);

	CCArray *waypoints;

	void addWaypoints();

	BOOL circle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo);
	void ccFillPoly(CCPoint* poli, int points, BOOL closePolygon);
	void enemyGotKilled();
	void getHpDamage();

	int wave;
	CCLabelBMFont *ui_wave_lbl;
	CCArray* enemies;
	BOOL loadWave();

	int playerHp;
	CCLabelBMFont *ui_hp_lbl;
	BOOL gameEnded;

	void doGameOver();

	int playerGold;
	CCLabelBMFont *ui_gold_lbl;

	void awardGold(int gold);
};

#endif // __HELLOWORLD_SCENE_H__
