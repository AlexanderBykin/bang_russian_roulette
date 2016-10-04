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

#ifndef __BrrClient__RoomItem__
#define __BrrClient__RoomItem__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "MessageResponseRoomInfo.pb.h"

USING_NS_CC;
using namespace ui;

class RoomItem : public Widget {
    const Color4B _bgColor = Color4B(0, 0, 0, 125);
    const Color4B _bgSelectedColor = Color4B(0, 0, 0, 180);
    const Color3B _textColor = Color3B(151, 239, 187);
    const Color3B _textSelectedColor = Color3B(255, 220, 72);
    const int _bgColorTag = 100;
public:
    static RoomItem *create(MessageResponseRoomInfo *roomItem, float width, float height);
    bool init(MessageResponseRoomInfo *roomItem, float width, float height);
    void setSelection(bool value);
    long long getRoomId();
private:
    long long _roomId = 0L;
};

#endif /* defined(__BrrClient__RoomItem__) */
