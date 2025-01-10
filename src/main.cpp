#include <Geode/Geode.hpp>
FLAlertLayer* info_alert = nullptr;
using namespace geode::prelude;
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
class $modify(ModPauseLayer, PauseLayer) {

    void customSetup() {
        PauseLayer::customSetup();

        auto winSize = CCDirector::get()->getWinSize();
        auto level = PlayLayer::get()->m_level;

        auto menu = this->getChildByID("left-button-menu");

        auto btn_spr = CCSprite::createWithSpriteFrameName("GJ_restartCheckBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            btn_spr,
            this,
            menu_selector(ModPauseLayer::onCheckpoint)
        );

        btn->setID("info-button");
        btn->setPosition({ menu->getContentSize().width / 2, btn->getContentSize().height / 2 });
        menu->addChild(btn);
        menu->updateLayout();

    }
    void onCheckpoint(CCObject * sender) {
        FLAlertLayer::create(
            "Checkpoint",    // title
            "Your progress is being <cg>saved</c> live.",  // content
            "OK"        // button
        )->show();
    }
    void onResume(CCObject * sender) {
        PauseLayer::onResume(sender);
    }
};
#include <Geode/modify/PlayLayer.hpp>

class $modify(ModPlayLayer, PlayLayer) {
public:
    bool init() {

        return true;
    }

    void printPlayerPosition(PlayerObject& player) {
        float posX = player.getPosition().x;
        float posY = player.getPosition().y;

        log::info(fmt::format("Player Position: x = {} y = {}", posX, posY));
    }





};