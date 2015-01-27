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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    TTFConfig menu_title;
    menu_title.fontFilePath = "yuweij.ttf";
    menu_title.fontSize = 70;
    auto menu_label = Label::createWithTTF(menu_title, "<开始>");
    menu_label->setColor(Color3B::BLACK);
    menu_label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/4));
    this->addChild(menu_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(70);
    auto startItem = MenuItemFont::create("      ", CC_CALLBACK_1(StartScene::menuStartCallback, this));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/4));
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
//    auto label = Label::createWithBMFont("start.fnt", "谁是卧底");
//    //label->setScale(2);
//    label->setBlendFunc(BlendFunc::ADDITIVE);
//    label->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 120;
    auto label = Label::createWithTTF(title, "谁是卧底？");
    label->setColor(Color3B::BLACK);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.5));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "StartScene" splash screen"
    auto sprite = Sprite::create("background.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    //reset word here
    WordsManager::getInstance()->init();
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("contra.m4a");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button-28.wav");
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("contra.m4a");
    
    return true;
}


void StartScene::menuStartCallback(Ref* pSender)
{
    auto Rolescene = RoleScene::createScene();
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, Rolescene));
}
