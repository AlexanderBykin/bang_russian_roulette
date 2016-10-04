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

#ifndef __BrrClient__RotateRadian__
#define __BrrClient__RotateRadian__

#include "cocos2d.h"
#include "RotateRadianDelegate.h"

USING_NS_CC;

class RotateRadian : public ActionInterval {
public:
    static RotateRadian* create(float duration, double radianStart, double radianFinish, bool roomClockWise, bool withRoomClockWise, RotateRadianDelegate *delegate);
    bool init(float duration, double radianStart, double radianFinish, bool roomClockWise, bool withRoomClockWise, RotateRadianDelegate *delegate);
private:
    RotateRadianDelegate *_delegate;
    double _radianStart;
    double _radianFinish;
    bool _isClockWise;
    bool _withRoomClockWise;
    double _distance;
    void update(float time);
    const std::map<std::string, std::string> calculateClockWiseWithDistanceFromSourceRadian(double sourceRadian, double destRadian);
};

#endif
