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

#ifndef _GLOBALPROPERTIES_H
#define _GLOBALPROPERTIES_H

#define GameFont "Fonts/arial_bold.ttf"

#include "cocos2d.h"

class GlobalProperties {
public:
    static GlobalProperties* getInstance();
    static bool getIsMusicOn();
    static void setIsMusicOn(bool value);
    static bool getIsEffectsOn();
    static void setIsEffectsOn(bool value);
    static const char* getServerHost();
    static int getServerPort();
    static cocos2d::LanguageType getCurrentLanguage();
    static const std::string getCurrentLanguageAsString();
    static void setCurrentLanguage(cocos2d::LanguageType value);
    static float getScaleFactor();
    static void setScaleFactor(float value);
    static long getPlayerId();
    static void setPlayerId(long long value);
    static const std::string getLogin();
    static void setLogin(const std::string &value);
    static const std::string getPassword();
    static void setPassword(const std::string &value);
    static bool isDebug();
    GlobalProperties();
    void init();
    ~GlobalProperties();
private:
    float _scaleFactor;
};

#endif
