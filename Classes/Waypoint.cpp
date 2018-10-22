#include "Waypoint.h"

Waypoint::Waypoint()
{

}
Waypoint::~Waypoint()
{

}

Waypoint* Waypoint::create()
{
	Waypoint* obj = new Waypoint();
	if (obj && obj->init())
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return NULL;
}

bool Waypoint::init()
{

	return true;
}


Waypoint* Waypoint::createWithTheGame(HelloWorld* _game, CCPoint location)
{
	Waypoint* obj = new Waypoint();
	if (obj && obj->initWithTheGame(_game, location))
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return NULL;
}

bool Waypoint::initWithTheGame(HelloWorld* _game, CCPoint location)
{
	if (CCNode::init()) 
	{
		theGame = _game;
		this->setPosition(CCPointZero);
		myPosition = location;
		nextWaypoint = NULL;

		theGame->addChild(this);
		return true;
	}

	return false;
}

void Waypoint::draw()
{
	ccDrawColor4B(0, 255, 2, 255);
	ccDrawCircle(myPosition, 6, 360, 30, false);
	ccDrawCircle(myPosition, 2, 360, 30, false);

	if (nextWaypoint)
		ccDrawLine(myPosition, nextWaypoint->myPosition);

	CCNode::draw();
}
