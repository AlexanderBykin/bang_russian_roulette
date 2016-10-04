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

#include "DialogBase.h"
#include "GlobalProperties.h"
#include "audio/include/AudioEngine.h"
#include "Button9TextShadow.h"

USING_NS_CC;

bool DialogBase::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    _dialogRect = Rect(170,
                       170,
                       winSize.width - 340,
                       winSize.height - 340);
    
//    auto nodeColor = LayerColor::create(Color4B(0, 100, 0, 255));
//    nodeColor->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
//    nodeColor->setContentSize(_dialogRect.size);
//    nodeColor->setPosition(_dialogRect.origin);
//    this->addChild(nodeColor, 999);
    
    auto *bgSprite = Sprite::create("Dialog/DialogBaseBG.png");
    bgSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(bgSprite, 0);
    
    // dialog caption
    
    auto _dialogCaption = Label::createWithTTF("", GameFont, 48);
    _dialogCaption->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    _dialogCaption->setDimensions(_dialogRect.size.width-20, 100);
    _dialogCaption->setAlignment(TextHAlignment::CENTER, TextVAlignment::TOP);
    _dialogCaption->setPosition(Vec2(_dialogRect.origin.x + _dialogRect.size.width / 2, _dialogRect.origin.y + _dialogRect.size.height - 10));
    _dialogCaption->setColor(Color3B(255, 243, 192));
    this->addChild(_dialogCaption, _captionTag, _captionTag);
    
    return true;
}

void DialogBase::setDelegate(DialogDelegate *delegate) {
    _delegate = delegate;
}

Rect DialogBase::getDialogRect() {
    return _dialogRect;
}

void DialogBase::setCaption(const std::string caption) {
    auto dialogCaption = dynamic_cast<Label*>(this->getChildByTag(_captionTag));
    dialogCaption->setString(caption);
}

void DialogBase::setIsCloseable(bool value) {
    _isCloseable = value;

    if(_isCloseable) {
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->onTouchBegan = CC_CALLBACK_2(DialogBase::onTouchBegan, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(DialogBase::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    } else {
        _eventDispatcher->removeEventListener(_touchListener);
        CC_SAFE_DELETE(_touchListener);
    }
}

void DialogBase::onCancelDoneTap(Ref *sender) {
    auto node = dynamic_cast<Node*>(sender);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    if(_delegate) {
        _delegate->onDialogButtonTap(this, node->getTag(), {});
    }
}

void DialogBase::addDoneButton(const std::string &value) {
    this->addDoneButton(value, CC_CALLBACK_1(DialogBase::onCancelDoneTap, this));
}

void DialogBase::addDoneButton(const std::string &value, const ccMenuCallback &callback) {
    if (this->getChildByTag(DialogBaseButtons::btnDoneTag)) {
        return;
    }
    
    auto btn = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                              Size(450, 120),
                                              value,
                                              GameFont,
                                              47,
                                         Color3B(51, 51, 51),
                                         Color3B(204, 204, 204),
                                              callback);
    btn->setTag(DialogBaseButtons::btnDoneTag);
    btn->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    btn->setPosition(Vec2(_dialogRect.origin.x + _dialogRect.size.width - 20,
                          _dialogRect.origin.y + 20));
    this->addChild(btn, 1, DialogBaseButtons::btnDoneTag);
}

void DialogBase::addCancelButton(const std::string &value) {
    if (this->getChildByTag(DialogBaseButtons::btnCancelTag)) {
        return;
    }
    
    auto btn = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                         Size(450, 120),
                                         value,
                                         GameFont,
                                         47,
                                         Color3B(51, 51, 51),
                                         Color3B(204, 204, 204),
                                         CC_CALLBACK_1(DialogBase::onCancelDoneTap, this));
    btn->setTag(DialogBaseButtons::btnCancelTag);
    btn->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    btn->setPosition(Vec2(_dialogRect.origin.x + 20,
                          _dialogRect.origin.y + 20));
    this->addChild(btn, 1, DialogBaseButtons::btnCancelTag);
}

void DialogBase::addCustomButton(const std::string &value, const Vec2 &position, int tag) {
    if (this->getChildByTag(tag)) {
        return;
    }
    
    auto btn = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                         Size(450, 120),
                                         value,
                                         GameFont,
                                         47,
                                         Color3B(51, 51, 51),
                                         Color3B(204, 204, 204),
                                         CC_CALLBACK_1(DialogBase::onCancelDoneTap, this));
    btn->setTag(tag);
    btn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    btn->setPosition(position);
    this->addChild(btn, 1, tag);
}

bool DialogBase::onTouchBegan(Touch *touch, Event *event) {
    return _isCloseable;
}

void DialogBase::onTouchEnded(Touch *touch, Event *event) {
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    Rect _glRect = CC_RECT_POINTS_TO_PIXELS(_dialogRect);
    
    if (_glRect.containsPoint(location)) {
        return;
    }
    
    if (_delegate) {
        _delegate->onDialogButtonTap(this, DialogBaseButtons::btnCancelTag, {});
    }
}
