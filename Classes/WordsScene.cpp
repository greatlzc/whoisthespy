//
//  WordsScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "WordsScene.h"
#include "PlayingScene.h"
#include "WordsSceneDefine.h"
#include "Banker.h"

USING_NS_CC;

Scene* WordsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WordsScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WordsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (  !LayerColor::initWithColor(Color4B(36, 44, 60, 255))  )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    TTFConfig ttf;
    ttf.fontFilePath = "Abberancy.ttf";
    ttf.fontSize = 90;
    auto label = Label::createWithTTF(ttf, "Select Mode:");
    label->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.5));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "StartScene" splash screen"
//    auto sprite = Sprite::create("sky.jpg");
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto define = MenuItemFont::create("自定义", CC_CALLBACK_1(WordsScene::defineCallback, this));
    auto define_menu = Menu::create(define, NULL);
    define_menu->setPosition(Vec2(label->getPositionX()/2, label->getPositionY()/2));
    this->addChild(define_menu, 1);
    
    auto defaultm = MenuItemFont::create("随机", CC_CALLBACK_1(WordsScene::defaultCallback, this));
    auto default_menu = Menu::create(defaultm, NULL);
    default_menu->setPosition(Vec2(label->getPositionX()/0.66, label->getPositionY()/2));
    this->addChild(default_menu, 1);
    
    return true;
}


void WordsScene::defineCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    auto defineScene = WordsSceneDefine::createScene();
    Director::getInstance()->replaceScene(defineScene);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}

void WordsScene::defaultCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    //remove last played words
    WordsManager::getInstance()->removeWord(Banker::getInstance()->getWords());
    
    Banker::getInstance()->setWords(WordsManager::getInstance()->getWordsbyRandom());
    auto playingScene = PlayingScene::createScene();
    Director::getInstance()->replaceScene(playingScene);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}