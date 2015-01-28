//
//  PlayingScene.h
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#ifndef __HelloWorldDemo__PlayingScene__
#define __HelloWorldDemo__PlayingScene__

#include <cocos2d.h>

class PlayingScene : public cocos2d::Layer
{
private:
    int mPlayerSelected;
    bool isGameEnded;
    bool isModal;
public:
    
    PlayingScene() { mPlayerSelected = -1; isGameEnded = false; isModal = false; }
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuStartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayingScene);
    
    void OnForgotWord(Ref* pSender);
    
    void OnKillPlayer(Ref* pSender);
    
    void OnNameTouched(Ref* pSender, int seq);
    
    void update(float dt);
};

#endif /* defined(__HelloWorldDemo__PlayingScene__) */
