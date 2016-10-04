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

#include "DialogPutBullet.h"
#include "LanguageManager.h"
#include "Utils.h"
#include "GlobalProperties.h"
#include "audio/include/AudioEngine.h"
#include "Button9TextShadow.h"

DialogPutBullet* DialogPutBullet::create(int possibleAmountBullets) {
    DialogPutBullet *node = new (std::nothrow) DialogPutBullet();
    if(node && node->init(possibleAmountBullets)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool DialogPutBullet::init(int possibleAmountBullets) {
    if(!DialogBase::init()) {
        return false;
    }
    
    _possibleAmountBullets = possibleAmountBullets;
    
    this->setCaption(LanguageManager::getString("DialogPutBulletsCaption"));
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    
    auto pistolDrum = Sprite::create("Dialog/DialogPutBulletsPistolDrum.png");
    pistolDrum->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pistolDrum->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 35));
    this->addChild(pistolDrum);
    
    double angleAvg = Utils::getAverageAngleByAmount(6);
    double nextAngle = angleAvg * 0.5;
    
    for (int i = 0; i < 6; i++) {
        _bullets[i] = false;
        auto btnBullet = Button9TextShadow::create("Dialog/DialogPutBulletsBulletHoleOff.png", "Dialog/DialogPutBulletsBulletHoleOn.png", CC_CALLBACK_1(DialogPutBullet::onMenuCallback, this));
        btnBullet->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        btnBullet->setTag(i + 1);
        
        if (GlobalProperties::isDebug()) {
            auto lblPos = Label::createWithTTF(StringUtils::format("%i", i + 1), GameFont, 24);
            lblPos->setColor(Color3B::WHITE);
            lblPos->setPosition(Vec2(btnBullet->getContentSize().width / 2, btnBullet->getContentSize().height / 2));
            btnBullet->addChild(lblPos);
        }
        
        double circle = 160;
        Vec2 xyPos = Utils::getCenteredXYPositionByCircle(circle, nextAngle, Vec2(winSize.width / 2, winSize.height / 2));
        
        btnBullet->setPosition(Vec2(xyPos.x, xyPos.y));
        this->addChild(btnBullet);
        
        nextAngle -= angleAvg;
    }
    
    auto bgAvailableBullets = Sprite::create("Dialog/DialogPutBulletsBulletHoleOn.png");
    bgAvailableBullets->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    bgAvailableBullets->setPosition(Vec2(this->_dialogRect.origin.x + this->_dialogRect.size.width - 90, this->_dialogRect.origin.y + this->_dialogRect.size.height / 2));
    this->addChild(bgAvailableBullets);
    
    auto lblAvailableBullets = Label::createWithTTF("0", GameFont, 24);
    lblAvailableBullets->setColor(Color3B(255, 243, 192));
    lblAvailableBullets->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    lblAvailableBullets->setPosition(Vec2(bgAvailableBullets->getPosition().x + bgAvailableBullets->getContentSize().width / 4, bgAvailableBullets->getPosition().y));
    this->addChild(lblAvailableBullets, 1, SceneTags::lblAvailableBulletsTag);
    this->setAvailableBullets(_possibleAmountBullets);
    
    this->addDoneButton(LanguageManager::getString("DialogPutBulletsNextButton"), CC_CALLBACK_1(DialogPutBullet::onMenuCallback, this));
    
    return true;
}

void DialogPutBullet::onMenuCallback(Ref* sender) {
    auto node = dynamic_cast<Node*>(sender);
    switch (node->getTag()) {
        case DialogBaseButtons::btnDoneTag: {
            experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
            if(_delegate) {
                std::map<std::string, std::string> _data;
                for(int i=0; i<6; i++){
                    _data.insert(std::pair<std::string, std::string>(StringUtils::format("%d", i+1), StringUtils::format("%d", _bullets[i])));
                }
                _delegate->onDialogButtonTap(this, DialogBaseButtons::btnDoneTag, _data);
            }
            break;
        }
            
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6: {
            int insertedBullets = 0;
            for(int i=0; i<6; i++){
                if (_bullets[i] == true) {
                    insertedBullets++;
                }
            }
            
            if (insertedBullets == _possibleAmountBullets) {
                return;
            }
            
            experimental::AudioEngine::play2d("Sounds/switch_click.mp3");
            
            this->setAvailableBullets(_possibleAmountBullets - (insertedBullets + 1));
            
            bool bullet = _bullets[node->getTag()];
            
            bullet = !bullet;
            
            _bullets[node->getTag()] = bullet;
            
            if (bullet) {
                dynamic_cast<Button9TextShadow*>(node)->onPressStateChangedToPressed();
            }
            else {
                dynamic_cast<Button9TextShadow*>(node)->onPressStateChangedToNormal();
            }
            break;
        }
            
        default:
            break;
    }
}

void DialogPutBullet::setAvailableBullets(int value) {
    dynamic_cast<Label*>(this->getChildByTag(SceneTags::lblAvailableBulletsTag))->setString(StringUtils::format("%d", value));
}