//
//  GameUtils.cpp
//  whospy
//
//  Created by greatlzc on 1/28/15.
//
//

#include "GameUtils.h"

Size GameUtils::getVisibleSize()
{
    return Director::getInstance()->getVisibleSize();
}

Vec2 GameUtils::getOrigin()
{
    return Director::getInstance()->getVisibleOrigin();
}