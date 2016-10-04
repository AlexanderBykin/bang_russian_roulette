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

#ifndef __BrrClient__CCMenuItemImageLabel__
#define __BrrClient__CCMenuItemImageLabel__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MenuItemImageLabel: public MenuItemSprite {
    float _originalScale;
public:
    static MenuItemImageLabel* create(const std::string &bgImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const ccMenuCallback& callback);
    bool init(const std::string &bgImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const ccMenuCallback& callback);
    void activate();
    void selected();
    void unselected();
    void setText(const std::string &value);
    virtual ~MenuItemImageLabel();
};

#endif /* defined(__BrrClient__CCMenuItemImageLabel__) */
