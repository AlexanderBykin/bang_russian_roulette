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

#ifndef __BrrClient__LanguageManager__
#define __BrrClient__LanguageManager__

#include "cocos2d.h"
#include "json/document.h"
#include "json/rapidjson.h"

class LanguageManager : public cocos2d::Ref {
public:
	static LanguageManager* getInstance();
    static const std::string getString(const std::string &key);
    static void initLanguage();
    ~LanguageManager();
private:
    rapidjson::Document _document; // current document with language data
};

#endif
