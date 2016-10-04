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

#ifndef __BrrClient__Button9TextShadow__
#define __BrrClient__Button9TextShadow__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class Button9TextShadow: public ui::Button {
public:
    static Button9TextShadow* create(const std::string &bgImage, const Size& size, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const ccMenuCallback& callback);
    bool init(const std::string &bgImage, const Size& size, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const ccMenuCallback& callback);
    static Button9TextShadow* create(const std::string &bgImage, const ccMenuCallback& callback);
    bool init(const std::string &bgImage, const ccMenuCallback& callback);
    static Button9TextShadow* create(const std::string &bgImage, const std::string &bgImageSelected, const ccMenuCallback& callback);
    bool init(const std::string &bgImage, const std::string &bgImageSelected, const ccMenuCallback& callback);
    void setText(const std::string &value);
    void addContentChild(Node* node);
    void setSelectedResources(const std::string &bgImage, const cocos2d::Color3B &labelColor, const cocos2d::Color3B &labelShadowColor);
    void onPressStateChangedToNormal() override;
    void onPressStateChangedToPressed() override;
private:
    Node *contentNode = nullptr;
    ccMenuCallback tapCallback = nullptr;
    Color3B _lblNormalColor;
    Color3B _lblShadowNormalColor;
    Color3B _lblSelectedColor;
    Color3B _lblShadowSelectedColor;
    void touchEvent(Ref *pSender, TouchEventType type);
};


#endif /* defined(__BrrClient__Button9TextShadow__) */
