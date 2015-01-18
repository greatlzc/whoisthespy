//
//  StartScene.cpp
//  StartSceneDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "StartScene.h"
#include "RoleScene.h"

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
    auto startItem = MenuItemImage::create(
                                           "play 2.png",
                                           "play2 2.png",
                                           CC_CALLBACK_1(StartScene::menuStartCallback, this));
    startItem->setScale(0.6);
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/4));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    TTFConfig ttf;
    ttf.fontFilePath = "Abberancy.ttf";
    ttf.fontSize = 90;
    auto label = Label::createWithTTF(ttf, "Who's the Spy?");
    label->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.5));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "StartScene" splash screen"
    auto sprite = Sprite::create("sky.jpg");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    //reset word here
    WordsManager::getInstance()->init();
    
    return true;
}


void StartScene::menuStartCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    auto Rolescene = RoleScene::createScene();
    Director::getInstance()->replaceScene(Rolescene);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}
