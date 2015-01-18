//
//  ResultScene.h
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#ifndef __HelloWorldDemo__ResultScene__
#define __HelloWorldDemo__ResultScene__

#include <cocos2d.h>

class ResultScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuStopCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(ResultScene);
};

#endif /* defined(__HelloWorldDemo__ResultScene__) */
