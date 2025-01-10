#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/binding/GJGameLevel.hpp> 
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>  
using json = nlohmann::json;  

using namespace geode::prelude;

class $modify(ModPauseLayer, PauseLayer) {
public:
    


    void saveLevelProgress(float dt) {
        // data
        auto level = PlayLayer::get()->m_level;
        auto levelName = level->m_levelName;
        auto levelID = level->m_levelID;
        auto player1 = PlayLayer::get()->m_player1;
        auto player2 = PlayLayer::get()->m_player2;
        auto player1PosX = player1->m_positionX;
        auto player1PosY = player1->m_positionY;
        auto player2PosX = player2->m_positionX;
        auto player2PosY = player2->m_positionY;
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        json current;
        current["level"] = { {"name", levelName}, {"id", std::to_string(levelID)} };
        current["player"] = {
            {"player1", {{"x", std::to_string(player1PosX)}, {"y", std::to_string(player1PosY)}}},
            {"player2", {{"x", std::to_string(player2PosX)}, {"y", std::to_string(player2PosY)}}}
        };
        current["timestamp"] = std::to_string(timestamp);

        // load
        std::ifstream inFile("level_progress.json");
        json allProgress;
        if (inFile.is_open()) {
            inFile >> allProgress;
            inFile.close();
        }

        // replace
        allProgress["levels"][std::to_string(levelID)] = current;

        // write
        std::ofstream outFile("level_progress.json");
        outFile << std::setw(4) << allProgress << std::endl;
        outFile.close();
        log::debug("level progress has saved.");
    }


    void customSetup() {
        float saveInterval = 5.0f; 
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
        this->schedule(schedule_selector(ModPauseLayer::saveLevelProgress), 5, kCCRepeatForever, 0);
    }

    
    void onCheckpoint(CCObject * sender) {
        auto level = PlayLayer::get()->m_level;
        auto levelName = level->m_levelName;
        auto levelID = level->m_levelID;
        auto isPlatformer = PlayLayer::get()->m_isPlatformer;
        log::info("Platformer? {}, in {}", isPlatformer, levelName);

        if (isPlatformer) {
            FLAlertLayer::create(
                "Checkpoint",
                "Progress in this level is <cg>being saved</c>.",
                "OK"
            )->show();
        }
        else {
            FLAlertLayer::create(
                "Checkpoint",
                "Progress in this level is <cr>not being saved</c>.",
                "OK"
            )->show();
        }
    }

    void onResume(CCObject * sender) {
        PauseLayer::onResume(sender);
    }
};
