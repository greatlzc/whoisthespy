#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
//    typedef struct tagResource
//    {
//        cocos2d::Size size;
//        char directory[100];
//    }Resource;
//    
//    static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
//    static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
//    static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };
//    static cocos2d::Size designResolutionSize = cocos2d::Size(1136, 640);
//    
//    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
//    
//    Size frameSize = glview->getFrameSize();
    
    
    
//    if (frameSize.width < largeResource.size.width) {
//        director->setContentScaleFactor(largeResource.size.width/frameSize.width);
//    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = StartScene::createScene();
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("contra_title.mp3");
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
