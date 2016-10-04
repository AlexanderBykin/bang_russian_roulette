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

#ifndef __BrrClient__DialogAuth__
#define __BrrClient__DialogAuth__

#include "cocos2d.h"
#include "DialogBase.h"
#include "ui/UIEditBox/UIEditBox.h"

USING_NS_CC;
using namespace ui;

class DialogAuth : public DialogBase, public EditBoxDelegate {
public:
    enum DialogAuthMode {
        Auth, Register, ForgotPassword, VerifyEmail
    };
    static DialogAuth* create(const DialogAuthMode &mode);
    bool init(const DialogAuthMode &mode);
private:
    enum SceneTags {
        edEmailTag = 100,
        edPasswordTag,
        edNameTag,
        edVerifyTag
    };
    DialogAuthMode _dialogMode;
    void onMenuCallback(cocos2d::Ref *sender);
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
};

#endif
