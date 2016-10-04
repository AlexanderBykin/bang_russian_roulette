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

#ifndef __BrrClient__LabelShadow__
#define __BrrClient__LabelShadow__

#include "cocos2d.h"

USING_NS_CC;

class LabelShadow: public cocos2d::Node {
    const int _labelTag = 314;
    const int _labelShadowTag = 315;
public:
    static LabelShadow *create(const std::string &text, const std::string &fontName, float fontSize, const Color3B &textColor, const Color3B &textShadowColor);
    bool init(const std::string &text, const std::string &fontName, float fontSize, const Color3B &textColor, const Color3B &textShadowColor);
    void setTextColor(const Color3B &color);
    void setTextShadowColor(const Color3B &color);
    void setText(const std::string &value);
    void setShadowOffset(const float offset);
    void setAnchorPoint(const Vec2& point);
};

#endif /* defined(__BrrClient__LabelShadow__) */
