//
//  NameScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "NameScene.h"
#include "WordsScene.h"
#include "Banker.h"

USING_NS_CC;

Scene* NameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NameScene::init()
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
                                           CC_CALLBACK_1(NameScene::menuStartCallback, this));
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
    
//    TTFConfig ttf;
//    ttf.fontFilePath = "Abberancy.ttf";
//    ttf.fontSize = 90;
//    auto label = Label::createWithTTF(ttf, "Type the Names:");
//    label->setColor(Color3B::YELLOW);
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height/1.5));
    
    // add the label as a child to this layer
    //this->addChild(label, 1);
    
    // add "StartScene" splash screen"
//    auto sprite = Sprite::create("sky.jpg");
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    TextFieldTTF* text = TextFieldTTF::textFieldWithPlaceHolder("<点此输入姓名：>", "Arial", 70);
    text->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2));
    //text->attachWithIME();
    //text->setColorSpaceHolder(Color3B::GREEN);
    text->setTag(1);
    text->setDelegate(this);
    this->addChild(text);
    
//    auto touchListener = EventListenerTouchOneByOne::create();
//    
//    touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event * event) -> bool {
//        try {
//            // Show the on screen keyboard
//            auto textField = dynamic_cast<TextFieldTTF *>(event->getCurrentTarget());
//            textField->attachWithIME();
//            return true;
//        }
//        catch(std::bad_cast & err){
//            return true;
//        }
//    };
//    
//    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, text);
    
    //an invisible menu for the textfield
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(70);
    auto blank = MenuItemFont::create("                          ", CC_CALLBACK_1(NameScene::textFieldPressed, this));
    auto blank_menu = Menu::create(blank, NULL);
    blank_menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/2));
    this->addChild(blank_menu);
    
    int remain = Banker::getInstance()->numSpy +
    Banker::getInstance()->numGuy +
    Banker::getInstance()->numLucky -
    Banker::getInstance()->playerCount();
    std::stringstream ss;
    ss<<"还需输入 "<<remain<<" 个";
    
    auto label = LabelTTF::create(ss.str().c_str(), "Arial", 70);
    //label->setColor(Color3B::YELLOW);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.5));
    label->setTag(2);
    this->addChild(label, 1);
    
    scheduleUpdate();
    return true;
}


void NameScene::menuStartCallback(Ref* pSender)
{
    int remain = Banker::getInstance()->numSpy +
    Banker::getInstance()->numGuy +
    Banker::getInstance()->numLucky -
    Banker::getInstance()->playerCount();
    
    if (remain != 0) {
        return;
    }
    
    auto wordsScene = WordsScene::createScene();
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, wordsScene));
}

bool NameScene::onTextFieldAttachWithIME(TextFieldTTF *sender)
{
    if (Banker::getInstance()->isPlayersFull()) {
        return true;
    }
    //move away from the virtula keyboard
    this->setPosition(Vec2(0, 150));
    return TextFieldDelegate::onTextFieldAttachWithIME(sender);
}

bool NameScene::onTextFieldDetachWithIME(TextFieldTTF* sender)
{
    //move back
    this->setPosition(Vec2(0, 0));
    
    auto text = (TextFieldTTF*)this->getChildByTag(1);
    Player* newPlayer = new Player(text->getString());
    Banker::getInstance()->addPlayer(newPlayer);
    
    text->setString("");
    return TextFieldDelegate::onTextFieldDetachWithIME(sender);
}

void NameScene::textFieldPressed(Ref* pSender)
{
    auto text = (TextFieldTTF*)this->getChildByTag(1);
    text->attachWithIME();
}

bool NameScene::onTextFieldInsertText(TextFieldTTF *sender, const char *text, size_t nLen) {
    return TextFieldDelegate::onTextFieldInsertText(sender, text, nLen);
}

bool NameScene::onTextFieldDeleteBackward(TextFieldTTF *sender, const char *delText, size_t nLen) {
    return TextFieldDelegate::onTextFieldDeleteBackward(sender, delText, nLen);
}

bool NameScene::onVisit(TextFieldTTF *sender, Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    return TextFieldDelegate::onVisit(sender, renderer, transform, flags);
}

void NameScene::update(float dt)
{
    int remain = Banker::getInstance()->numSpy +
    Banker::getInstance()->numGuy +
    Banker::getInstance()->numLucky -
    Banker::getInstance()->playerCount();
    
    auto label = (LabelTTF *)this->getChildByTag(2);
    auto text = (TextFieldTTF*)this->getChildByTag(1);
    
    if (remain) {
        std::stringstream ss;
        ss<<"还需输入 "<<remain<<" 个";
        label->setString(ss.str().c_str());
    }
    else {
        label->setString("输入完成。");
        text->setString("<点击下一步>");
    }
    
}