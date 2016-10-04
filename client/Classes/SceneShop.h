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

#ifndef __BrrClient__SceneShop__
#define __BrrClient__SceneShop__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/UIListView.h"
#include "Libs/ProtoMessageDelegate.h"
#include "ProtoMessages/MessageResponseShopItem.pb.h"
#include "ProtoMessages/MessageRequestShopItemList.pb.h"
#include "ProtoMessages/MessageRequestBuyShopItem.pb.h"
#include "Dialog/DialogBase.h"
#include "PluginIAP/PluginIAP.h"
//#include "PluginVungle/PluginVungle.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class SceneShop : public Layer, public ProtoMessageDelegate, public DialogDelegate, public sdkbox::IAPListener {
        //, public sdkbox::VungleListener {
public:
    bool init() override;
    void onMenuCallback(Ref* ref);
    void onListViewSelectedItemEvent(Ref *sender, ListView::EventType type);
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) override;
    CREATE_FUNC(SceneShop);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
private:
    enum SceneTags {
        _miBackTag = 120,
        _listViewItemsTag,
        _menuShopItemTag,
        _miItemsTypeTag,
        _miCollectionTypeTag,
        _miMoneyTypeTag,
        _miWatchAdTag,
        _menuBuyButtonsTag,
        _miRealCashTag,
        _miInGameCashTag,
        _txtMoneyTag,
        _txtDescriptionTag,
        _txtRealCashPriceTag,
        _txtInGameCashPriceTag,
        _imgInGameCashPriceTag
    };
    DialogTypes _currentDialog = DialogTypes::DialogTypeNone;
    int _lastSelectedShopItemIndex = -1;
    int _lastSelectedShopItemType = -1;
    int _lastSelectedItem = 0;
    std::vector<sdkbox::Product> _inAppItems;
    void delayInit(float value);
    void showBuyButtonsByShopItemType();
    void showDialog(DialogTypes dialogType);
    void hideDialog();
    void onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) override;
    void authPlayer();
    void setMoney(long long value);
    void getShopItemByType(MessageRequestShopItemList_eShopItemType shopItemType);
    void setPriceForRealMoney(const std::string& value);
    void setPriceForInGameCash(int value);
    void setRealCashIsVisible(bool value);
    void setGameCashIsVisible(bool value);
    void setWatchAdIsVisible(bool value);
    void setEnableControls(bool value);
    // api call
    void getMoney();
    void buyShopItemWithName(const std::string& shopItemName, MessageRequestBuyShopItem_eBuyType buyType, const char *receipt);
    // api callbacks
    void callbackNeedAuth(const std::string &source);
    void callbackAuth(const std::string &source);
    void callbackShopItems(const std::string &source);
    void callbackGetMoney(const std::string &source);
    void callbackBuyShopItem(const std::string &source);
    void callbackWatchAd(const std::string &source);
    // iap
    void onInitialized(bool ok) override;
    void onSuccess(const sdkbox::Product& p) override;
    void onFailure(const sdkbox::Product& p, const std::string& msg) override;
    void onCanceled(const sdkbox::Product& p) override;
    void onRestored(const sdkbox::Product& p) override;
    void onProductRequestSuccess(const std::vector<sdkbox::Product>& products) override;
    void onProductRequestFailure(const std::string& msg) override;
    void onRestoreComplete(bool ok, const std::string &msg) override;
    // vungle
//    void onVungleCacheAvailable();
//    void onVungleStarted();
//    void onVungleFinished();
//    void onVungleAdViewed(bool isComplete);
//    void onVungleAdReward(const std::string& name);
};

#endif
