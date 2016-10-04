/*
 Bang Russian Roulette (client) - This is real online and multiplayer game published at Google Play.
 Copyright (C) 2016  Alexander Shniperson
 Email: alex.shniperson@gmail.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AppDelegate.h"
#include "Libs/SceneManager.h"
#include "Libs/ProtoMessageDelegate.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "Libs/GlobalProperties.h"
#include "Network/SocketThread.h"
#include "ProtoMessages/MessageResponse.pb.h"
#include <array>

USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
    return 0; //flag for packages manager
}

// Information about resources
typedef struct tagResource {
    cocos2d::Size size; // The size that this resource is designed for
    char directory[100]; // The name of teh directory containing resources of this type
} Resource;

// Define all our resource types and locations
static Resource ultraResource   =  { Size(2048, 1536), "UD"};
static Resource hiResource      =  { Size(1920, 1080), "HD" };
static Resource stdResource     =  { Size(960, 640),   "SD" };
static Resource lowResource     =  { Size(570, 320),   "LD" };

bool AppDelegate::applicationDidFinishLaunching() {
    // Declare the resolution we designed the game at
    Size designResolutionSize = hiResource.size;

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("BrrClient", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("BrrClient");
#endif
        director->setOpenGLView(glview);
    }

    // Declare an array containing the resource descriptions, from largest to smallest
    std::array<Resource, 4> resources {{ ultraResource, hiResource, stdResource, lowResource }};
    
    // Tell cocos our design resolution and our resolution policy
    director->getOpenGLView()->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
    
    // The vector we will use to build a list of paths to search for resources
    std::vector<std::string> searchPaths;
    
    // Get the actual screen size
    Size frameSize = glview->getFrameSize();
    
    // Define a silly scale factor so we know when we have calculated it
    float scaleFactor = -1;
    int widthDiff = 999;
    Resource found = ultraResource; // Default to this in case we find a resolution we plain can't figure out!
    
    // Look through our resource definitions
    for (auto resource : resources) {
        // Calculate the Horizontal ratio for the resouces (i.e. Resource Height / Device Height
        float ratio = resource.size.height / frameSize.height;
        
        // Calculate the scaled widths based on the horizontal ratio
        float scaleWidth = resource.size.width / ratio;
        
        // Calculate the Width Differences (i.e. how much bigger is the resource than the screen, width wise- so how many pixels are we going to lose?
        int diff = (int) (scaleWidth - frameSize.width);
        
        // If the width difference is < -1 we'd have black bars, so ignore it (single pixel is fine!)
        // If the scale factor is > 2 we're scaling a bit too much, ignore it
        // If the scale factor is < 0.5 we're scaling a bit to much, ignore it
        if (diff >= -1 && ratio <= 2 && ratio >= 0.5) {
            // Use this one if it is the lowest width difference
            if (diff < widthDiff) {
                widthDiff = diff;
                found = resource;
                scaleFactor = resource.size.height / designResolutionSize.height;
                GlobalProperties::setScaleFactor(designResolutionSize.height / resource.size.height);
                if (GlobalProperties::isDebug()) {
                    log(">>> FOUND %s frame(%f, %f) resource(%f, %f) ratio(%f) scaleWidth(%f) diff(%d)",
                        resource.directory,
                        frameSize.width, frameSize.height,
                        resource.size.width, resource.size.height,
                        ratio, scaleWidth, diff);
                }
            }
        } else {
            if (GlobalProperties::isDebug()) {
                log(">>> NOTFOUND %s frame(%f, %f) resource(%f, %f) ratio(%f) scaleWidth(%f) diff(%d)",
                    resource.directory,
                    frameSize.width, frameSize.height,
                    resource.size.width, resource.size.height,
                    ratio, scaleWidth, diff);
            }
        }
    }
    
    
    // only for test
    //found = stdResource;
    //scaleFactor = found.size.height / designResolutionSize.height;
    //GlobalProperties::setScaleFactor(designResolutionSize.height / found.size.height);
    
    
    // so now we should have found which resource to use
    searchPaths.push_back(found.directory);
    
    if (GlobalProperties::isDebug()) {
        log("Using %s widthDiff %d ScaleFactor %.2f",
            found.directory,
            widthDiff,
            GlobalProperties::getScaleFactor());
    }
    
    director->setContentScaleFactor(scaleFactor);
    
    searchPaths.push_back("Fonts");
    searchPaths.push_back("Localization");
    FileUtils::getInstance()->setSearchPaths(searchPaths);

    // turn on display FPS
    //director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval((float) (1.0 / 60));
    
    register_all_packages();
    
    sdkbox::PluginSdkboxPlay::setListener(this);
    sdkbox::PluginSdkboxPlay::init();
    sdkbox::PluginGoogleAnalytics::init();
    sdkbox::PluginGoogleAnalytics::startSession();
    sdkbox::PluginGoogleAnalytics::logScreen("AppDelegate");
    sdkbox::PluginGoogleAnalytics::logEvent("Resolution", StringUtils::format("%fx%f", found.size.width, found.size.height), "", 0);
    
    SocketThread::getInstance()->setDelegate(this);

    SceneManager::goNext(BrrScenes::SceneIntro);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    sdkbox::PluginGoogleAnalytics::stopSession();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    sdkbox::PluginGoogleAnalytics::startSession();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::onSocketMessageReceive(const std::string &data) {
    if(auto currentScene = Director::getInstance()->getRunningScene()) {
        if(auto transitionScene = dynamic_cast<TransitionScene*>(currentScene)) {
            if(auto protoScene = dynamic_cast<ProtoMessageDelegate*>(transitionScene->getInScene()->getChildByTag(ProtoMessageDelegate::ProtoMessageSceneID))) {
                protoScene->onProtoMessageReceive(data);
            }
        }
        else if(auto protoScene = dynamic_cast<ProtoMessageDelegate*>(currentScene->getChildByTag(ProtoMessageDelegate::ProtoMessageSceneID))) {
            protoScene->onProtoMessageReceive(data);
        } else {
            if (GlobalProperties::isDebug()) {
                log("onSocketMessageReceive ProtoScene is NULL");
            }
        }
    } else {
        if (GlobalProperties::isDebug()) {
            log("onSocketMessageReceive ProtoScene is NULL");
        }
    }
}

void AppDelegate::onSocketError(const std::string &msg) {
    if (GlobalProperties::isDebug()) {
        log("SocketError '%s'", msg.c_str());
    }
    SocketThread::getInstance()->getSocket()->Close();
}

// SdkboxPlay

void AppDelegate::onConnectionStatusChanged(int status) {
}

void AppDelegate::onScoreSubmitted(const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday) {
    
}

void AppDelegate::onIncrementalAchievementUnlocked(const std::string& achievement_name) {
    
}

void AppDelegate::onIncrementalAchievementStep(const std::string& achievement_name, int step) {
    
}

void AppDelegate::onAchievementUnlocked(const std::string& achievement_name, bool newlyUnlocked) {
    
}
