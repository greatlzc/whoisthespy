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

std::string GameUtils::getBGsource()
{
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    std::string bgSource;
    if (frameSize.width == 1024) {
        bgSource = "iPad.png";
    }
    else if (frameSize.width == 1136)
    {
        bgSource = "iPhone5.png";
    }
    else if (frameSize.width == 1334)
    {
        bgSource = "iPhone6.png";
    }
    else if (frameSize.width == 2048)
    {
        bgSource = "iPad Retina.png";
    }
    else if (frameSize.width == 2208)
    {
        bgSource = "iPhone6+.png";
    }
    else
    {
        bgSource = "background.png";
    }
    
    return bgSource;
}