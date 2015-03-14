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
public:
    
    PlayingScene() { mPlayerSelected = -1; isGameEnded = false; }
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    friend class ForgotDialog;
    friend class KillDialog;
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayingScene);
    
    void OnForgotWord(Ref* pSender);
    
    void OnKillPlayer(Ref* pSender);
    
    void OnNameTouched(Ref* pSender, int seq);
    
    void update(float dt);
};

//a DoModal dialog for forgetting word
class ForgotDialog : public cocos2d::Layer
{
public:
    virtual bool init();
    
    CREATE_FUNC(ForgotDialog);
    
    void OnForgotWord(Ref* pSender);
    
private:
    cocos2d::Sprite* forgotLabel;
    cocos2d::Label* word;
    cocos2d::Label* info;
    bool doModal;
};

//a DoModal dialog for killing one player
class KillDialog : public cocos2d::Layer
{
public:
    virtual bool init();
    
    CREATE_FUNC(KillDialog);
    
    void OnKillPlayer(Ref* pSender);
    
private:
    cocos2d::Sprite* killLabel;
    cocos2d::Label* result;
    cocos2d::Label* info;
    bool doModal;
};

#define NO_PLAYING_SCENE 1
#define NO_FORGOT_DIALOG 2
#define NO_KILL_DIALOG   3

#endif /* defined(__HelloWorldDemo__PlayingScene__) */
