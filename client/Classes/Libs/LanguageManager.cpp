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

#include "LanguageManager.h"
#include "GlobalProperties.h"

USING_NS_CC;

static LanguageManager* _instance = nullptr;

LanguageManager* LanguageManager::getInstance() {
    if(_instance == nullptr) {
        _instance = new (std::nothrow) LanguageManager();
        LanguageManager::initLanguage();
    }
    return _instance;
}

LanguageManager::~LanguageManager() {
    if(_instance != nullptr) {
        delete _instance;
    }
}

void LanguageManager::initLanguage() {
    if(_instance->_document.IsArray() && !_instance->_document.Empty()) {
        _instance->_document.Clear();
    }
    
    std::string fileName;
    // detect current language
    switch(GlobalProperties::getCurrentLanguage())
    {
        case LanguageType::ENGLISH:
            fileName = "en.json";
            break;
        case LanguageType::RUSSIAN:
            fileName = "ru.json";
            break;
        default:
            log("Unknown language. Use english");
            fileName = "en.json";
            break;
    };
    
    // below we open, read and parse language data file with rapidjson library
    std::string clearContent = FileUtils::getInstance()->getStringFromFile(fileName);
    
    _instance->_document.Parse<0>(clearContent.c_str());
    if(_instance->_document.HasParseError()) {
        if (GlobalProperties::isDebug()) {
            log("Language file parsing error!");
        }
        return;
    }
}

const std::string LanguageManager::getString(const std::string &key) {
    return LanguageManager::getInstance()->_document[key.c_str()].GetString();
}