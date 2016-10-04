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

#ifndef __BrrClient__DialogBase__
#define __BrrClient__DialogBase__

#include "cocos2d.h"

enum DialogTypes {
    DialogTypeNone = 1000,
    DialogTypeBase,
    DialogTypeAction,
    DialogTypeRole,
    DialogTypeAuth,
    DialogTypeRegister,
    DialogTypeForgotPassword,
    DialogTypeVerifyEmail,
    DialogTypePutBullets,
    DialogTypePlayerInfo,
    DialogTypePlayerBet,
    DialogTypeUseItems,
    DialogTypeDuel
};

class DialogDelegate {
public:
    virtual void onDialogButtonTap(cocos2d::Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) = 0;
};

class DialogBase : public cocos2d::Layer {
public:
    enum DialogBaseButtons {
        btnCancelTag = 50,
        btnDoneTag = 51
    };
    bool init() override;
    CREATE_FUNC(DialogBase);
    void setDelegate(DialogDelegate* delegate);
    void setCaption(const std::string caption);
    void setIsCloseable(bool value);
    void addDoneButton(const std::string &value);
    void addDoneButton(const std::string &value, const cocos2d::ccMenuCallback& callback);
    void addCancelButton(const std::string &value);
    void addCustomButton(const std::string &value, const cocos2d::Vec2 &position, int tag);
    cocos2d::Rect getDialogRect();
    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;
    void onTouchEnded(cocos2d::Touch*, cocos2d::Event*) override;
    void onCancelDoneTap(Ref* sender);
protected:
    const int _captionTag = 10;
    bool _isCloseable;
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    DialogDelegate* _delegate;
    cocos2d::Rect _dialogRect;
};

#endif 
