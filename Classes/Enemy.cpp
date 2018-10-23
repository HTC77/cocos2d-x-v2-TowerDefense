#include "Enemy.h"
#include "SimpleAudioEngine.h"

#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_ORIGIN -10

Enemy::Enemy()
{

}
Enemy::~Enemy()
{

}

Enemy* Enemy::create()
{
	Enemy* obj = new Enemy();
	if (obj && obj->init())
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return NULL;
}

bool Enemy::init()
{
	return true;
}


Enemy* Enemy::createWithTheGame(HelloWorld* _game)
{
	Enemy* obj = new Enemy();
	if (obj && obj->initWithTheGame(_game))
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return NULL;
}

bool Enemy::initWithTheGame(HelloWorld* _game)
{
	if (!CCNode::init())
	{
		return false;
	}

	theGame = _game;
	maxHp = 40;
	currentHp = maxHp;

	active = NO;

	walkingSpeed = 0.5;

	mySprite = CCSprite::create("enemy.png");
	this->addChild(mySprite);

	Waypoint * waypoint = (Waypoint *) theGame->waypoints->objectAtIndex(theGame->waypoints->count() - 1);

	destinationWaypoint = waypoint->nextWaypoint;

	CCPoint pos = waypoint->myPosition;
	myPosition = pos;

	mySprite->setPosition(pos);

	theGame->addChild(this);

	this->scheduleUpdate();

	attackedBy = new CCArray(5);
	return true;
}

void Enemy::doActivate(float dt)
{
	active = YES;
}

void Enemy::update(float dt)
{
	if (!active) return;

	if (theGame->circle(myPosition, 1, destinationWaypoint->myPosition,1))
	{
		if (destinationWaypoint->nextWaypoint)
		{
			destinationWaypoint = destinationWaypoint->nextWaypoint;
		}
		else
		{
			//Reached the end of the road. Damage the player
			theGame->getHpDamage();
			this->getRemoved();
		}
	}

	CCPoint targetPoint = destinationWaypoint->myPosition;
	float movementSpeed = walkingSpeed;

	CCPoint normalized = ccpNormalize(ccp(targetPoint.x - myPosition.x, targetPoint.y - myPosition.y));
	mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)));

	myPosition = ccp(myPosition.x + normalized.x * movementSpeed,
		myPosition.y + normalized.y * movementSpeed);

	mySprite->setPosition(myPosition);
}

void Enemy::getRemoved()
{
	CCObject* t = NULL;
	CCARRAY_FOREACH(attackedBy,t)
	{
		Tower* attacker = (Tower*)t;
		attacker->targetKilled();
	}

	this->removeFromParentAndCleanup(YES);

	theGame->enemies->removeObject(this);

	//Notify the game that we killed an enemy so we can check if we can send another wave
	theGame->enemyGotKilled();
}

void Enemy::draw()
{
	ccDrawSolidRect(
		ccp(myPosition.x + HEALTH_BAR_ORIGIN,myPosition.y + 16),
		ccp(myPosition.x + HEALTH_BAR_ORIGIN + HEALTH_BAR_WIDTH,
		myPosition.y + 14),
		ccc4f(1.0, 0, 0, 1.0)
	);

	ccDrawSolidRect(
		ccp(myPosition.x + HEALTH_BAR_ORIGIN,myPosition.y + 16),
		ccp(myPosition.x + HEALTH_BAR_ORIGIN + (float)(currentHp * HEALTH_BAR_WIDTH) / maxHp,
		myPosition.y + 14),
		ccc4f(0, 1.0, 0, 1.0)
	);
}

void Enemy::getAttacked(Tower* attacker)
{
	attackedBy->addObject(attacker);
}

void Enemy::gotLostSight(Tower* attacker)
{
	attackedBy->removeObject(attacker);
}

void Enemy::getDamaged(int damage)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("laser_shoot.wav");

	currentHp -= damage;
	if (currentHp <= 0)
	{
		theGame->awardGold(200);
		this->getRemoved();
	}
}