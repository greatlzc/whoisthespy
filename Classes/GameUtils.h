//
//  GameUtils.h
//  whospy
//
//  Created by greatlzc on 1/28/15.
//
//

#ifndef __whospy__GameUtils__
#define __whospy__GameUtils__

#include <cocos2d.h>

USING_NS_CC;

class GameUtils
{
public:
    static Size getVisibleSize();
    static Vec2 getOrigin();
    static std::string getBGsource();
};

#define ORIGIN_X GameUtils::getOrigin().x
#define ORIGIN_Y GameUtils::getOrigin().y
#define WIDTH GameUtils::getVisibleSize().width
#define HEIGHT GameUtils::getVisibleSize().height
#define BGSRC GameUtils::getBGsource()

#endif /* defined(__whospy__GameUtils__) */
