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

#ifndef __BrrClient__ShopItemUsed__
#define __BrrClient__ShopItemUsed__

#include "cocos2d.h"
#include "RotateRadianDelegate.h"

USING_NS_CC;

#define ShopItemUsedDidFinishAnimationNotification "ShopItemUsedDidFinishAnimation"

class ShopItemUsed : public Layer, public RotateRadianDelegate {
public:
    static ShopItemUsed* create(std::string shopItemName, double sourcePlayerRadian, double destPlayerRadian, long long destPlayerId);
    bool init(std::string shopItemName, double sourcePlayerRadian, double destPlayerRadian, long long destPlayerId);
    void setRadian(double value);
    void animate();
    void setOpacity(GLubyte value);
    const std::string getShopItemName();
    long long getDestPlayerId();
private:
    enum SceneTags {
        bgTag = 100
    };
    double _sourcePlayerRadian;
    double _destPlayerRadian;
    double _currentRadian;
    bool _isAnimationEnabled;
    double _radius;
    Vec2 _center;
    std::string _shopItemName;
    long long _destPlayerId;
    void didFinishAnimation();
    void updatePosition();
};

#endif 
