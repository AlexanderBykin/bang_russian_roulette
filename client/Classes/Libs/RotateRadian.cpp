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

#include "RotateRadian.h"

RotateRadian* RotateRadian::create(float duration, double radianStart, double radianFinish, bool roomClockWise, bool withRoomClockWise, RotateRadianDelegate *delegate) {
    RotateRadian *node = new (std::nothrow) RotateRadian();
    if(node && node->init(duration, radianStart, radianFinish, roomClockWise, withRoomClockWise, delegate)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool RotateRadian::init(float duration, double radianStart, double radianFinish, bool roomClockWise, bool withRoomClockWise, RotateRadianDelegate *delegate) {
    if(!ActionInterval::initWithDuration(duration)) {
        return false;
    }
    
    _delegate = delegate;
    _radianStart = radianStart;
    _radianFinish = radianFinish;
    _withRoomClockWise = withRoomClockWise;
    if (_withRoomClockWise) {
        _isClockWise = roomClockWise;
    } else {
        auto calculated = this->calculateClockWiseWithDistanceFromSourceRadian(_radianStart, _radianFinish);
        _isClockWise = calculated.at("clockWise").compare("1") == 0;
        _distance = std::atof(calculated.at("distance").c_str());
    }
    
    return true;
}

void RotateRadian::update(float time) {
    if (_delegate) {
        double val = 0;
        
        if (_withRoomClockWise)
            val = (_radianFinish - _radianStart) * ((_isClockWise) ? -time : time) + _radianFinish;
        else
            val = _distance * ((_isClockWise) ? -time : time) + _radianStart;
        
        //        NSLog(@"radianNew(%f)", val);
        _delegate->setRadian(val);
    }
}

const std::map<std::string, std::string> RotateRadian::calculateClockWiseWithDistanceFromSourceRadian(double sourceRadian, double destRadian) {
    double coClockWise, clockWise = 0;
    
    if (sourceRadian < destRadian) {
        coClockWise = destRadian - sourceRadian;
        clockWise = 2 * M_PI + sourceRadian - destRadian;
    }
    else {
        coClockWise = 2 * M_PI - sourceRadian + destRadian;
        clockWise = sourceRadian - destRadian;
    }
    
    if (coClockWise <= clockWise)
        return {
            {"clockWise", "0"},
            {"distance", StringUtils::format("%f", coClockWise)}
        };
    else
        return {
            {"clockWise", "1"},
            {"distance", StringUtils::format("%f", clockWise)}
        };
}