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

#ifndef __BrrClient__RoomLamp__
#define __BrrClient__RoomLamp__

#include "cocos2d.h"

USING_NS_CC;

class RoomLamp : public Layer {
public:
    static RoomLamp* create(const std::string &label, bool isOn);
    bool init(const std::string &label, bool isOn);
    void setIsLampOn(bool value);
    void setText(const std::string &text);
    void setOpacity(GLubyte value);
    void fadeOut();
private:
    enum SceneTags {
        lampTag = 100,
        lblTag
    };
    bool _isLampOn;
    std::string _text;
};

#endif 