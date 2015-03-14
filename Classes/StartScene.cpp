//
//  StartScene.cpp
//  StartSceneDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "StartScene.h"
#include "RoleScene.h"
#include "SimpleAudioEngine.h"
#include "GameUtils.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(36, 44, 60, 255)) )
    {
        return false;
    }

    TTFConfig menuTitle;
    menuTitle.fontFilePath = "yuweij.ttf";
    menuTitle.fontSize = 70;
    auto menuLabel = Label::createWithTTF(menuTitle, "<开始>");
    menuLabel->setColor(Color3B::BLACK);
    menuLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                                 ORIGIN_Y + HEIGHT/4));
    this->addChild(menuLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto startItem = MenuItemFont::create("      ", CC_CALLBACK_1(StartScene::menuStartCallback, this));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                           ORIGIN_Y + HEIGHT/4));
    this->addChild(menu, 1);
    
    TTFConfig gameTitle;
    gameTitle.fontFilePath = "yuweij.ttf";
    gameTitle.fontSize = 120;
    auto gameLabel = Label::createWithTTF(gameTitle, "谁是卧底？");
    gameLabel->setColor(Color3B::BLACK);
    gameLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                            ORIGIN_Y + HEIGHT/1.5));
    
    // add the label as a child to this layer
    this->addChild(gameLabel, 1);
    
    // add "StartScene" splash screen"
    auto background = Sprite::create(BGSRC);
    
    // position the sprite on the center of the screen
    background->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    
    // add the sprite as a child to this layer
    this->addChild(background, 0);
    
    //reset word here
    WordsManager::getInstance()->init();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("opening.mp3");
    
    return true;
}


void StartScene::menuStartCallback(Ref* pSender)
{
    auto Rolescene = RoleScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, Rolescene));
}
