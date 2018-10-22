#ifndef __TowerDefense__HUDLayer__
#define __TowerDefense__HUDLayer__

#pragma once

#include "cocos2d.h"
USING_NS_CC;

class HUDLayer : public CCLayer
{
public:
	HUDLayer();
	~HUDLayer();
	static HUDLayer* create();
	bool init();
	
};

#endif

