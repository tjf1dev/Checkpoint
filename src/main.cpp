#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/binding/GJGameLevel.hpp> 
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>  
using json = nlohmann::json;

using namespace geode::prelude;
#include <Geode/modify/PlayLayer.hpp>
//⠀⢸⠂⠀⠀⠀⠘⣧⠀⠀⣟⠛⠲⢤⡀⠀⠀⣰⠏⠀⠀⠀⠀⠀⢹⡀
//⠀⡿⠀⠀⠀⠀⠀⠈⢷⡀⢻⡀⠀⠀⠙⢦⣰⠏⠀⠀⠀⠀⠀⠀⢸⠀
//⠀⡇⠀⠀⠀⠀⠀⠀⢀⣻⠞⠛⠀⠀⠀⠀⠻⠀⠀⠀⠀⠀⠀⠀⢸⠀
//⠀⡇⠀⠀⠀⠀⠀⠀⠛⠓⠒⠓⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀
//⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀                        by tjf1
//⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⠀⠀⢀⡟⠀                       5.01.2025
//⠀⠘⣇⠀⠘⣿⠋⢹⠛⣿⡇⠀⠀⠀⠀⣿⣿⡇⠀⢳⠉⠀⣠⡾⠁⠀                uhh this code barely works
//⣦⣤⣽⣆⢀⡇⠀⢸⡇⣾⡇⠀⠀⠀⠀⣿⣿⡷⠀⢸⡇⠐⠛⠛⣿⠀
//⠹⣦⠀⠀⠸⡇⠀⠸⣿⡿⠁⢀⡀⠀⠀⠿⠿⠃⠀⢸⠇⠀⢀⡾⠁⠀
//⠀⠈⡿⢠⢶⣡⡄⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⣴⣧⠆⠀⢻⡄⠀⠀
//⠀⢸⠃⠀⠘⠉⠀⠀⠀⠠⣄⡴⠲⠶⠴⠃⠀⠀⠀⠉⡀⠀⠀⢻⡄⠀
//⠀⠘⠒⠒⠻⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⠞⠛⠒⠛⠋⠁⠀
//⠀⠀⠀⠀⠀⠀⠸⣟⠓⠒⠂⠀⠀⠀⠀⠀⠈⢷⡀⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⠀⠀⠀⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⠀⠀⠀⣼⣃⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⠀⠀⠀⠉⣹⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⠀⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡆⠀⠀⠀⠀⠀

class $modify(ModPauseLayer, PauseLayer) {
public:



    void saveLevelProgress(float dt) {

        // data
        auto level = PlayLayer::get()->m_level;
        auto levelName = level->m_levelName;
        auto levelID = level->m_levelID;
        auto isPlatformer = level->isPlatformer();
        auto player1 = PlayLayer::get()->m_player1;
        auto player2 = PlayLayer::get()->m_player2;
        auto player1PosX = PlayLayer::get()->m_player1->getPositionX();
        auto player1PosY = PlayLayer::get()->m_player1->getPositionY();
        auto player2PosX = PlayLayer::get()->m_player2->getPositionX();
        auto player2PosY = PlayLayer::get()->m_player2->getPositionY();
        auto groundLayer = PlayLayer::get()->m_groundLayer;
        auto groundLayer2 = PlayLayer::get()->m_groundLayer2;
        auto now = std::chrono::system_clock::now();
        auto player1gamemode = "";
		auto player2gamemode = "";
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

        // get gamemode

        // p1
        if (player1->m_isShip) {
            player1gamemode = "1"; // ship - 1
        }
        else if (player1->m_isBall) {
			player1gamemode = "2"; // ball - 2
        }
        else if (player1->m_isDart) {
			player1gamemode = "3"; // wave - 3
        }
        else if (player1->m_isSpider) {
			player1gamemode = "4"; // spider - 4
        }
		else if (player1->m_isSwing){
			player1gamemode = "5"; // swing - 5
        }
        else if (player1->m_isBird) {
			player1gamemode = "6"; // ufo - 6
        }
		else if (player1->m_isRobot) {
			player1gamemode = "7"; // robot - 7
        }
        else {
			player1gamemode = "0"; // cube - 0
        }
        // p2

        if (player2->m_isShip) {
            player2gamemode = "1"; // ship - 1
        }
        else if (player2->m_isBall) {
            player2gamemode = "2"; // ball - 2
        }
        else if (player2->m_isDart) {
            player2gamemode = "3"; // wave - 3
        }
        else if (player1->m_isSpider) {
            player2gamemode = "4"; // spider - 4
        }
        else if (player1->m_isSwing) {
            player2gamemode = "5"; // swing - 5
        }
        else if (player1->m_isBird) {
            player2gamemode = "6"; // ufo - 6
        }
        else if (player1->m_isRobot) {
            player2gamemode = "7"; // robot - 7
        }
        else {
            player2gamemode = "0"; // cube - 0 OR doesnt exist
        }
        


        json current;
        current["level"] = { 
            {
                "name", levelName
            }, 
            {
                "id", std::to_string(levelID)
            },
            {
                "groundLayer",{
                    {"pos1", groundLayer->getPositionY()},
                    {"pos2", groundLayer2->getPositionY()}
                 }
             }
        };
        current["player"] = {
            {"player1", {
                {"x", std::to_string(player1PosX)},
                {"y", std::to_string(player1PosY)},
                {"gamemode", player1gamemode}
            }},
            {"player2", {
                {"x", std::to_string(player2PosX)},
                {"y", std::to_string(player2PosY)},
                {"gamemode", player2gamemode}
            }}
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
        log::debug("Progress for {} has been saved.", fmt::to_string(levelName));
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

    }
    void onCheckpoint(CCObject * sender) {
        auto level = PlayLayer::get()->m_level;
        auto levelName = level->m_levelName;
        auto levelID = level->m_levelID;
        auto isPlatformer = PlayLayer::get()->m_isPlatformer;
        if (isPlatformer) {

            FLAlertLayer::create(
                "Checkpoint",
                "Progress in this level is <cg>being saved</c>.",
                "OK"
            )->show();

            saveLevelProgress(1);



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
class $modify(ModPlayLayer, PlayLayer) {
    struct Fields {
        GJGameLevel* s_level;
    };

    bool init(GJGameLevel * level, bool useReplay, bool dontCreateObjects) {
        m_level = level;
        // wait until fully initialized

        auto save = Mod::get()->getSettingValue<bool>("saving");
        auto load = Mod::get()->getSettingValue<bool>("loading");
        if (save) {
            startAutoSave(level);
        }
        else {
            log::warn("Due to config settings, Checkpoint will not be saving progress for this level.");
        }
        if (load) {
            this->scheduleOnce(schedule_selector(ModPlayLayer::checkForSaves), 0);
        }
        else {
            log::warn("Due to config settings, Checkpoint will not be loading progress for this level.");
        }
        return PlayLayer::init(level, useReplay, dontCreateObjects);
    }
    void setPlayerMode(PlayerObject* player, const std::string& gamemode, bool isPlayer1) {
        // Disable all modes first
        player->toggleFlyMode(false, isPlayer1);
        player->toggleRollMode(false, isPlayer1);
        player->toggleDartMode(false, isPlayer1);
        player->toggleSpiderMode(false, isPlayer1);
        player->toggleSwingMode(false, isPlayer1);
        player->toggleBirdMode(false, isPlayer1);
        player->toggleRobotMode(false, isPlayer1);

        // Enable the selected mode
        if (gamemode == "1") {
            player->toggleFlyMode(true, isPlayer1); // Ship
        }
        else if (gamemode == "2") {
            player->toggleRollMode(true, isPlayer1); // Ball
        }
        else if (gamemode == "3") {
            player->toggleDartMode(true, isPlayer1); // Wave/Dart - failsafe (doesnt exist in plat)
        }
        else if (gamemode == "4") {
            player->toggleSpiderMode(true, isPlayer1); // Spider
        }
        else if (gamemode == "5") {
            player->toggleSwingMode(true, isPlayer1); // Swing - failsafe (doesnt exist in plat)
        }
        else if (gamemode == "6") {
            player->toggleBirdMode(true, isPlayer1); // UFO/Bird
        }
        else if (gamemode == "7") {
            player->toggleRobotMode(true, isPlayer1); // Robot
        }
        // If gamemode is not recognized, it defaults to Cube, and all are left disabled.
    }


    void checkForSaves(float dt) {
        // Load saved progress from the JSON file
        auto level = m_level;
        std::ifstream inFile("level_progress.json");
        nlohmann::json saveData;

        // this code doesnt work
        if (inFile.is_open()) {
            try {
                inFile >> saveData;
            }
            catch (const std::exception& e) {
                log::error("Failed to parse save file: {}", e.what());
                inFile.close();
                return;
            }
            inFile.close();
        }
        else {
            log::info("No save file found. Skipping save restoration.");
            return;
        }

        // Get the level ID as a string
        std::string levelID = std::to_string(level->m_levelID);
        log::info("Attempting to restore data...");
        // Check if there's saved data for the current level
        if (saveData.contains("levels") && saveData["levels"].contains(levelID)) {
            auto& levelData = saveData["levels"][levelID];
			auto groundLayer = PlayLayer::m_groundLayer;
            auto groundLayer2 = PlayLayer::m_groundLayer2;
            // Check if player data exists
            if (levelData.contains("player")) {
                auto& playerData = levelData["player"];

                if (levelData.contains("groundLayer")) {
                    auto d_groundLayer = levelData["groundLayer"]["pos1"];
                    auto d_groundLayer2 = levelData["groundLayer"]["pos2"];
                    groundLayer->setPositionY(d_groundLayer);
                    groundLayer2->setPositionY(d_groundLayer2);
                    log::info("Checkpoint found ground layers - {}, {}",
                        std::to_string(static_cast<float>(d_groundLayer)),
                        std::to_string(static_cast<float>(d_groundLayer2)));
                }

                // Restore player 1 position
                if (playerData.contains("player1")) {
					
                    auto& player1Data = playerData["player1"];
                    if (player1Data.contains("gamemode")) {
                        setPlayerMode(m_player1, player1Data["gamemode"].get<std::string>(), true);
                    }
                    
                    if (player1Data.contains("x") && player1Data.contains("y")) {
                        try {
                            float posX = std::stof(player1Data["x"].get<std::string>());
                            float posY = std::stof(player1Data["y"].get<std::string>());
                            m_player1->m_position.x = posX;
                            m_player1->m_position.y = posY;
                            log::info("Checkpoint found player 1 - {}, {}", posX, posY);
                        }
                        catch (const std::exception& e) {
                            log::error("Failed to restore Player 1 position: {}", e.what());
                        }
                    }
                }

                // Restore player 2 position
                if (playerData.contains("player2")) {
                    auto& player2Data = playerData["player2"];
                    setPlayerMode(m_player2, player2Data["gamemode"].get<std::string>(), true);
                    if (player2Data.contains("x") && player2Data.contains("y")) {
                        try {
                            float posX = std::stof(player2Data["x"].get<std::string>());
                            float posY = std::stof(player2Data["y"].get<std::string>());
                            m_player2->m_position.x = posX;
                            m_player2->m_position.y = posY;
                            log::info("Checkpoint found player 2 - {}, {}", posX, posY);
                        }
                        catch (const std::exception& e) {
                            log::error("Failed to restore Player 2 position: {}", e.what());
                        }
                    }
                }
            }
        }
        else {
            log::info("No saved progress found for level ID: {}", levelID);
        }
    }

    void onLevelLoad() {
        FLAlertLayer::create("Checkpoint", "There were saves found for this level, but Checkpoint was unable to load them.", "OK")->show();
    }

    void startAutoSave(GJGameLevel * level) {
        log::info("Entered: {}", level->m_levelName);
        if (level->isPlatformer()) {
            this->schedule(schedule_selector(ModPauseLayer::saveLevelProgress), 5, kCCRepeatForever, 0);
        }
    }
};