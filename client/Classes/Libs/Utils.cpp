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

#include "Utils.h"

Vec2 Utils::getCenteredXYPositionByCircle(double radius, double sourceAngle, Vec2 screenCenter) {
    return Vec2(radius * cos(sourceAngle) + screenCenter.x, radius * sin(sourceAngle) + screenCenter.y);
}

double Utils::getAverageAngleByAmount(int amount) {
    double result = 0;
    
    if (amount > 0) {
        result = 2 * M_PI / amount;
    }
    
    return result;
}

double Utils::getQuadraticSizes(Size source) {
    double result = 0;
    
    if (source.width > source.height) {
        result = source.height;
    }
    else {
        result = source.width;
    }
    
    if (source.width == source.height) {
        result = source.width;
    }
    
    return result;
}
