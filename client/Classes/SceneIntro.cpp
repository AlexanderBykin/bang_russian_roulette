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

#include "SceneIntro.h"
#include "GlobalProperties.h"
#include "SceneManager.h"

USING_NS_CC;

bool SceneIntro::init() {
    if (!Layer::init()) {
        return false;
    }

    Size winSize = Director::getInstance()->getVisibleSize();

    auto sprite = Sprite::create("SceneIntroBG.png");
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(sprite, 0);

    
    if (GlobalProperties::isDebug()) {
        auto lblTest = Label::createWithTTF("Только для тестирования\n(с) Шниперсон Александр", GameFont, 100);
        lblTest->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lblTest->setPosition(winSize.width/2, winSize.height/2);
        lblTest->setRotation(-45);
        lblTest->setOpacity(100);
        this->addChild(lblTest, 9999, 9999);
    }
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SceneIntro::delayInit), 1.5);
    
    return true;
}

void SceneIntro::delayInit(float value) {
    SceneManager::goNext(BrrScenes::SceneMain);
}