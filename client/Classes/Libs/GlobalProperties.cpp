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

#include "GlobalProperties.h"
#include "md5.h"
#include <string>

USING_NS_CC;

static GlobalProperties* _instance = nullptr;

GlobalProperties* GlobalProperties::getInstance() {
    if(_instance == nullptr) {
        _instance = new (std::nothrow) GlobalProperties();
        _instance->init();
    }
    return _instance;
}

GlobalProperties::GlobalProperties() {
}

void GlobalProperties::init() {
    auto userDefault = UserDefault::getInstance();
    if (!userDefault->getBoolForKey("settingsinit")) {
        userDefault->setBoolForKey("settingsinit", true);
        userDefault->flush();
        GlobalProperties::setIsMusicOn(true);
        GlobalProperties::setIsEffectsOn(true);
        GlobalProperties::setLogin("");
        GlobalProperties::setPassword("");
        GlobalProperties::setCurrentLanguage(Application::getInstance()->getCurrentLanguage());
    }
    GlobalProperties::setPlayerId(-1L);
}

GlobalProperties::~GlobalProperties() {
    if(_instance != nullptr) {
        delete _instance;
    }
}

bool GlobalProperties::getIsMusicOn() {
    GlobalProperties::getInstance();
    return UserDefault::getInstance()->getBoolForKey("ismusicon");
}

void GlobalProperties::setIsMusicOn(bool value) {
    GlobalProperties::getInstance();
    UserDefault::getInstance()->setBoolForKey("ismusicon", value);
}

bool GlobalProperties::getIsEffectsOn() {
    GlobalProperties::getInstance();
    return UserDefault::getInstance()->getBoolForKey("iseffectson");
}

void GlobalProperties::setIsEffectsOn(bool value) {
    GlobalProperties::getInstance();
    UserDefault::getInstance()->setBoolForKey("iseffectson", value);
}

const char* GlobalProperties::getServerHost() {
    return "orionlab.net";
}

int GlobalProperties::getServerPort() {
    return 15155;
}

LanguageType GlobalProperties::getCurrentLanguage() {
    GlobalProperties::getInstance();
    return (LanguageType)UserDefault::getInstance()->getIntegerForKey("language");
}

const std::string GlobalProperties::getCurrentLanguageAsString() {
    switch (GlobalProperties::getCurrentLanguage()) {
        case LanguageType::ENGLISH:
            return "en";
            
        case LanguageType::RUSSIAN:
            return "ru";
            
        default:
            return "en";
    }
}

void GlobalProperties::setCurrentLanguage(LanguageType value) {
    GlobalProperties::getInstance();
    UserDefault::getInstance()->setIntegerForKey("language", (int)value);
}

float GlobalProperties::getScaleFactor() {
    return GlobalProperties::getInstance()->_scaleFactor;
}

void GlobalProperties::setScaleFactor(float value) {
    GlobalProperties::getInstance()->_scaleFactor = value;
}

long GlobalProperties::getPlayerId() {
    GlobalProperties::getInstance();
    if(UserDefault::getInstance()->getStringForKey("playerid").empty()) {
        setPlayerId(-1L);
    }
    return std::atol(UserDefault::getInstance()->getStringForKey("playerid").c_str());
}

void GlobalProperties::setPlayerId(long long value) {
    GlobalProperties::getInstance();
    UserDefault::getInstance()->setStringForKey("playerid", StringUtils::format("%lli", value));
}

const std::string GlobalProperties::getLogin() {
    GlobalProperties::getInstance();
    return UserDefault::getInstance()->getStringForKey("login");
}

void GlobalProperties::setLogin(const std::string &value) {
    GlobalProperties::getInstance();
    UserDefault::getInstance()->setStringForKey("login", value);
}

const std::string GlobalProperties::getPassword() {
    GlobalProperties::getInstance();
    return UserDefault::getInstance()->getStringForKey("password");
}

void GlobalProperties::setPassword(const std::string &value) {
    GlobalProperties::getInstance();
    MD5 md5;
    std::string md5Hash = std::string(md5.digestString(value.c_str()));
    UserDefault::getInstance()->setStringForKey("password", md5Hash);
}

bool GlobalProperties::isDebug() {
    return false;
}
