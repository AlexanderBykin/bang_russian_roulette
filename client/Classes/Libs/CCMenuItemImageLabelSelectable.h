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

#ifndef __BrrClient__CCMenuItemImageLabelSelectable__
#define __BrrClient__CCMenuItemImageLabelSelectable__

#include "cocos2d.h"

USING_NS_CC;

class MenuItemImageLabelSelectable: public MenuItemSprite {
    Color3B _labelColor;
    Color3B _labelShadowColor;
    Color3B _labelSelectedColor;
    Color3B _labelSelectedShadowColor;
    const int _labelShadowTag = 314;
public:
    static MenuItemImageLabelSelectable* create(const std::string &bgImage, const std::string &bgSelectedImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const Color3B &labelSelectedColor, const Color3B &labelSelectedShadowColor, const ccMenuCallback& callback);
    bool init(const std::string &bgImage, const std::string &bgSelectedImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const Color3B &labelSelectedColor, const Color3B &labelSelectedShadowColor, const ccMenuCallback& callback);
    void selected();
    void unselected();
    virtual ~MenuItemImageLabelSelectable();
};

#endif 