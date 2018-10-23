#include "Tower.h"

Tower::Tower()
{

}
Tower::~Tower()
{

}

Tower* Tower::create()
{
	Tower* obj = new Tower();
	if (obj && obj->init())
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return NULL;
}

bool Tower::init()
{

	return true;
}

Tower* Tower::createWithTheGame(HelloWorld* _game, CCPoint location)
{
	Tower* obj = new Tower();
	if (obj && obj->initWithTheGame(_game, location))
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return NULL;
}

bool Tower::initWithTheGame(HelloWorld* _game, CCPoint location)
{
	if (!CCNode::init())
	{
		return false;
	}

	theGame = _game;
	attackRange = 70;
	damage = 10;
	fireRate = 1;

	mySprite = CCSprite::create("tower.png");
	this->addChild(mySprite);

	mySprite->setPosition(location);

	theGame->addChild(this);

	this->scheduleUpdate();
	
	chosenEnemy = NULL;

	return true;
}

void Tower::update(float dt)
{
	if (chosenEnemy){
		//We make it turn to target the enemy chosen
		CCPoint normalized = ccpNormalize(ccp(chosenEnemy->mySprite->getPositionX() - mySprite->getPositionX(),
			chosenEnemy->mySprite->getPositionY() - mySprite->getPositionY()));
		mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)) + 90);

		if (theGame->circle(mySprite->getPosition(), /* withRadius : */attackRange,
		/*collisionWithCircle : */chosenEnemy->mySprite->getPosition(),/* collisionCircleRadius :*/ 1))
		{
			this->lostSightOfEnemy();
		}
	}
	else {
		

		CCObject* e = NULL;
		CCARRAY_FOREACH(theGame->enemies,e)
		{
			Enemy* enemy = (Enemy*)e;
			if (theGame->circle(mySprite->getPosition(), /*withRadius : */attackRange,
			/*collisionWithCircle : */enemy->mySprite->getPosition(), /*collisionCircleRadius :*/ 1))
			{
				this->chosenEnemyForAttack(enemy);
				break;
			}
		}
	}
}
void Tower::draw()
{
	ccDrawColor4B(255, 255, 255, 255);
	ccDrawCircle(mySprite->getPosition(), attackRange, 360, 30, false);
	//CCNode::draw();
}

void Tower::attackEnemy()
{
	this->schedule(schedule_selector(Tower::shootWeapon), fireRate);
}

void Tower::chosenEnemyForAttack(Enemy *enemy)
{
	chosenEnemy = NULL;
	chosenEnemy = enemy;
	this->attackEnemy();
	enemy->getAttacked(this);
}

void Tower::shootWeapon(float dt)
{
	CCSprite* bullet = CCSprite::create("bullet.png");
	theGame->addChild(bullet);
	bullet->setPosition(mySprite->getPosition());
	bullet->runAction(CCSequence::create(
	CCMoveTo::create(0.1f,chosenEnemy->mySprite->getPosition()),
	CCCallFunc::create(this, callfunc_selector(Tower::damageEnemy)),
	CCCallFuncN::create(bullet,callfuncN_selector(Tower::removeBullet)), NULL));
}

void Tower::removeBullet(CCSprite *bullet)
{
	bullet->removeFromParentAndCleanup(true);
}

void Tower::damageEnemy()
{
	chosenEnemy->getDamaged(damage);
}

void Tower::targetKilled()
{
	if (chosenEnemy)
	chosenEnemy = NULL;
	CCLOG("BEFORE UNSC");
	this->unschedule(schedule_selector(Tower::shootWeapon));
}

void Tower::lostSightOfEnemy()
{
	chosenEnemy->gotLostSight(this);
	if (chosenEnemy)
		chosenEnemy = NULL;

	this->unschedule(schedule_selector(Tower::shootWeapon));
}