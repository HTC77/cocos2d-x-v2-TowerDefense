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

	return true;
}

void Tower::update(float dt)
{

}
void Tower::draw()
{
	ccDrawColor4B(255, 255, 255, 255);
	ccDrawCircle(mySprite->getPosition(), attackRange, 360, 30, false);
	//CCNode::draw();
}