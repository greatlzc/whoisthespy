//
//  WordsScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "WordsSceneDefine.h"
#include "Banker.h"
#include "PlayingScene.h"

USING_NS_CC;

Scene* WordsSceneDefine::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WordsSceneDefine::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WordsSceneDefine::init()
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
    auto startItem = MenuItemImage::create(
                                           "play 2.png",
                                           "play2 2.png",
                                           CC_CALLBACK_1(WordsSceneDefine::menuStartCallback, this));
    startItem->setScale(0.6);
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/5));
    
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
    auto label = Label::createWithTTF(ttf, "Input the words:");
    label->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.2));
    
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
    
    TextFieldTTF* common = TextFieldTTF::textFieldWithPlaceHolder("<点此输入平民词：>", "Arial", 70);
    common->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2));
    common->setTag(1);
    common->setDelegate(this);
    this->addChild(common);
    
    TextFieldTTF* spy = TextFieldTTF::textFieldWithPlaceHolder("<点此输入卧底词：>", "Arial", 70);
    spy->setPosition(Vec2(origin.x + visibleSize.width/2,
                          origin.x + visibleSize.height/2.7));
    spy->setTag(2);
    spy->setDelegate(this);
    this->addChild(spy);
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(70);
    
    //invisible menu for 平民 word
    auto blank1 = MenuItemFont::create("                          ", CC_CALLBACK_1(WordsSceneDefine::textFieldPressed, this, 1));
    auto blank_menu1 = Menu::create(blank1, NULL);
    blank_menu1->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/2));
    this->addChild(blank_menu1);
    
    //invisible menu for 卧底 word
    auto blank2 = MenuItemFont::create("                          ", CC_CALLBACK_1(WordsSceneDefine::textFieldPressed, this, 2));
    auto blank_menu2 = Menu::create(blank2, NULL);
    blank_menu2->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  spy->getPositionY()));
    this->addChild(blank_menu2);
    
    //scheduleUpdate();
    return true;
}


void WordsSceneDefine::menuStartCallback(Ref* pSender)
{
    auto gWord = (TextFieldTTF*)this->getChildByTag(1);
    auto sWord = (TextFieldTTF*)this->getChildByTag(2);
    if (gWord->getString() == "" || sWord->getString() == "")
    {
        return;
    }
    WordsManager::getInstance()->addWord(gWord->getString(), sWord->getString());
    Banker::getInstance()->setWords(WordsManager::getInstance()->getWordsbySelect());
    auto playingScene = PlayingScene::createScene();
    Director::getInstance()->replaceScene(playingScene);
}

bool WordsSceneDefine::onTextFieldAttachWithIME(TextFieldTTF *sender)
{
    this->setPosition(Vec2(0, 150));
    return TextFieldDelegate::onTextFieldAttachWithIME(sender);
}

bool WordsSceneDefine::onTextFieldDetachWithIME(TextFieldTTF* sender)
{
    this->setPosition(Vec2(0, 0));
//    if (sender->getTag() == 1)
//    {
//        auto text = (TextFieldTTF*)this->getChildByTag(1);
//        
//    }
//    else if (sender->getTag() == 2)
//    {
//        auto text = (TextFieldTTF*)this->getChildByTag(2);
//    }
    return TextFieldDelegate::onTextFieldDetachWithIME(sender);
}

void WordsSceneDefine::textFieldPressed(Ref* pSender, int index)
{
    if (index == 1) {
        auto text = (TextFieldTTF*)this->getChildByTag(1);
        text->attachWithIME();
    }
    else if (index == 2)
    {
        auto text = (TextFieldTTF*)this->getChildByTag(2);
        text->attachWithIME();
    }
}

bool WordsSceneDefine::onTextFieldInsertText(TextFieldTTF *sender, const char *text, size_t nLen) {
    return TextFieldDelegate::onTextFieldInsertText(sender, text, nLen);
}

bool WordsSceneDefine::onTextFieldDeleteBackward(TextFieldTTF *sender, const char *delText, size_t nLen) {
    return TextFieldDelegate::onTextFieldDeleteBackward(sender, delText, nLen);
}

bool WordsSceneDefine::onVisit(TextFieldTTF *sender, Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    return TextFieldDelegate::onVisit(sender, renderer, transform, flags);
}