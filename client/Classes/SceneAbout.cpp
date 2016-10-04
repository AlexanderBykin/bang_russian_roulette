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

#include "SceneAbout.h"
#include "SceneManager.h"
#include "extensions/cocos-ext.h"
#include "LanguageManager.h"
#include "GlobalProperties.h"
#include "ui/UIListView.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "audio/include/AudioEngine.h"
#include "Button9TextShadow.h"

USING_NS_CC;
using namespace ui;

bool SceneAbout::init() {
    if(!Layer::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("SceneAbout");
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("SceneAbout/SceneAboutBG.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg, 0);
    
    
    auto btnBack = Button9TextShadow::create("SceneAbout/btnSceneAboutBack.png", CC_CALLBACK_1(SceneAbout::onMenuCallback, this));
    btnBack->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    btnBack->setPosition(Vec2(10, winSize.height-15));
    this->addChild(btnBack, 1);

    
    auto listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(false);
    listView->setContentSize(Size(600, 600));
    listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    listView->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    // listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    // listView->setBackGroundColor(Color3B::GREEN);
    auto l1 = Widget::create();
    auto l1txt = Label::createWithSystemFont(LanguageManager::getString("AboutAuthorAndProgrammerLabel"), "Arial", 35);
    l1txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    l1->setContentSize(l1txt->getContentSize());
    l1txt->setColor(Color3B(206, 202, 255));
    l1->addChild(l1txt);
    listView->pushBackCustomItem(l1);
    auto l2 = Widget::create();
    auto l2txt = Label::createWithTTF(LanguageManager::getString("AboutAuthorAndProgrammerName"), GameFont, 50);
    l2txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    l2->setContentSize(l2txt->getContentSize());
    l2txt->setColor(Color3B(206, 202, 255));
    l2->addChild(l2txt);
    listView->pushBackCustomItem(l2);
    auto l3 = Widget::create();
    l3->setContentSize(Size(800, 60));
    listView->pushBackCustomItem(l3);
    auto l4 = Widget::create();
    auto l4txt = Label::createWithSystemFont(LanguageManager::getString("AboutDesignerLabel"), "Arial", 35);
    l4txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    l4->setContentSize(l4txt->getContentSize());
    l4txt->setColor(Color3B(206, 202, 255));
    l4->addChild(l4txt);
    listView->pushBackCustomItem(l4);
    auto l5 = Widget::create();
    auto l5txt = Label::createWithTTF(LanguageManager::getString("AboutDesignerName"), GameFont, 50);
    l5txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    l5->setContentSize(l5txt->getContentSize());
    l5txt->setColor(Color3B(206, 202, 255));
    l5->addChild(l5txt);
    listView->pushBackCustomItem(l5);
    auto l6 = Widget::create();
    l6->setContentSize(Size(800, 60));
    listView->pushBackCustomItem(l6);
    auto l7 = Widget::create();
    auto l7txt = Label::createWithSystemFont(LanguageManager::getString("AboutIllustratorLabel"), "Arial", 35);
    l7txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    l7->setContentSize(l7txt->getContentSize());
    l7txt->setColor(Color3B(206, 202, 255));
    l7->addChild(l7txt);
    listView->pushBackCustomItem(l7);
    auto l8 = Widget::create();
    auto l8txt = Label::createWithTTF(LanguageManager::getString("AboutIllustratorName"), GameFont, 50);
    l8txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    l8->setContentSize(l8txt->getContentSize());
    l8txt->setColor(Color3B(206, 202, 255));
    l8->addChild(l8txt);
    listView->pushBackCustomItem(l8);
    this->addChild(listView, 1, 2);
    
    auto sequence = Sequence::create(MoveTo::create(0, Vec2(listView->getPosition().x, 0)),
                                     MoveTo::create(16.0f, Vec2(listView->getPosition().x, winSize.height + listView->getContentSize().height+40)),
                                     NULL);
    listView->runAction(RepeatForever::create(sequence));
    
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SceneAbout::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    if (GlobalProperties::isDebug()) {
        auto lblTest = Label::createWithTTF("Только для тестирования\n(с) Шниперсон Александр", GameFont, 100);
        lblTest->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lblTest->setPosition(winSize.width/2, winSize.height/2);
        lblTest->setRotation(-45);
        lblTest->setOpacity(100);
        this->addChild(lblTest, 9999, 9999);
    }
    
    return true;
}

void SceneAbout::onMenuCallback(Ref *ref) {
    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBack", "", 0);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    SceneManager::goBack(BrrScenes::SceneMain);
}

void SceneAbout::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        this->onMenuCallback(nullptr);
    }
}

Layer* SceneAbout::createNewLineLayer(const cocos2d::Size value) {
    auto newLineLayer = Layer::create();
    newLineLayer->setContentSize(value);
    return newLineLayer;
}
