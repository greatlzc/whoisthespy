//
//  Player.h
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#ifndef __HelloWorldDemo__Player__
#define __HelloWorldDemo__Player__

#include <cocos2d.h>

enum ROLE{
    UNDEFINED = 0,
    GUY,
    LUCKY,
    SPY,
};

class Player
{
public:
    std::string mName;
    bool isDead;
    ROLE mRole;
    int mScore;
    
    Player();
    Player(const std::string &name) : mName(name), isDead(false), mRole(UNDEFINED), mScore(0) {};
};

#endif /* defined(__HelloWorldDemo__Player__) */
