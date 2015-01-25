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
    TTFConfig menu_title;
    menu_title.fontFilePath = "yuweij.ttf";
    menu_title.fontSize = 70;
    auto menu_label = Label::createWithTTF(menu_title, "<继续>");
    menu_label->setColor(Color3B::BLACK);
    menu_label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/7));
    this->addChild(menu_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(70);
    auto startItem = MenuItemFont::create("      ", CC_CALLBACK_1(WordsSceneDefine::menuStartCallback, this));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/7));
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 96;
    auto label = Label::createWithTTF(title, "输入词语");
    label->setColor(Color3B::BLACK);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.3));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    TextFieldTTF* guy = TextFieldTTF::textFieldWithPlaceHolder("{ 输入平民词 }", "Arial", 60);
    guy->setColor(Color3B::BLACK);
    guy->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/1.8));
    guy->setTag(1);
    guy->setDelegate(this);
    this->addChild(guy, 2);
    
    TextFieldTTF* spy = TextFieldTTF::textFieldWithPlaceHolder("{ 输入卧底词 }", "Arial", 60);
    spy->setColor(Color3B::BLACK);
    spy->setPosition(Vec2(origin.x + visibleSize.width/2,
                          origin.x + visibleSize.height/2.8));
    spy->setTag(2);
    spy->setDelegate(this);
    this->addChild(spy, 2);
    
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
    
    // background image
    auto sprite = Sprite::create("background.png");
    
    // position it on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
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
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, playingScene));
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