#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdio>
#include "Entity.h"

// 1. 存檔系統
void saveGame(const std::vector<Entity*>& party, int kills, int rounds) {
    std::ofstream outFile("save.txt");
    outFile << party[0]->getHp() << " " << party[0]->getAtk() << " " << party[0]->getCd() << " "
            << party[1]->getHp() << " " << party[1]->getAtk() << " " << party[1]->getCd() << " "
            << kills << " " << rounds << std::endl;
    outFile.close();
    std::cout << "\n[系統] 遊戲已完整儲存！" << std::endl;
}

// 2. 讀檔系統
void loadGame(std::vector<Entity*>& party, int& kills, int& rounds) {
    std::ifstream inFile("save.txt");
    if (!inFile) {
        party.push_back(new Warrior("勇者", 150, 20, 0));
        party.push_back(new Monster("怪物", 0, 0, 0));
        kills = 0; rounds = 0;
        return;
    }
    int vHp, vAtk, vCd, mHp, mAtk, mCd;
    inFile >> vHp >> vAtk >> vCd >> mHp >> mAtk >> mCd >> kills >> rounds;
    
    party.push_back(new Warrior("勇者", vHp, vAtk, vCd));
    party.push_back(new Monster("怪物", mHp, mAtk, mCd));
    inFile.close();
    std::cout << "[系統] 已載入上次進度。" << std::endl;
}

// 3. 刪檔/重置系統
void resetGame() {
    if (std::remove("save.txt") == 0) {
        std::cout << "\n[系統] 存檔已刪除，進度已重置！" << std::endl;
    } else {
        std::cout << "\n[系統] 目前沒有存檔可供刪除。" << std::endl;
    }
}

int main() {
    srand(time(0));
    std::vector<Entity*> gameEntities;
    int killCount = 0, roundCount = 0;
    
    loadGame(gameEntities, killCount, roundCount);
    
    while (gameEntities[0]->getHp() > 0) {
        std::cout << "\n--- [總回合: " << roundCount << "] 勇者 HP: " << gameEntities[0]->getHp() 
                  << " | 怪物 HP: " << gameEntities[1]->getHp() << " (ATK: " << gameEntities[1]->getAtk() << ") ---" << std::endl;
        
        std::cout << "1.攻擊 2.技能 3.迴避 4.存檔 5.離開 6.重置: ";
        int choice;
        std::cin >> choice;

        if (choice == 5) break;
        if (choice == 4) { saveGame(gameEntities, killCount, roundCount); continue; }
        if (choice == 6) { resetGame(); break; }
        
        bool dodged = false;
        bool actionPerformed = false;

        // 玩家行動
        if (choice == 1) { gameEntities[0]->attack(gameEntities[1]); actionPerformed = true; }
        else if (choice == 2) {
            if (gameEntities[0]->canUseSkill()) { gameEntities[0]->useSkill(gameEntities[1]); actionPerformed = true; }
            else std::cout << ">> 技能冷卻中！" << std::endl;
        }
        else if (choice == 3) {
            dodged = (rand() % 2 == 0);
            std::cout << (dodged ? ">> 成功閃避！" : ">> 閃避失敗！") << std::endl;
            actionPerformed = true;
        }

        // 怪物反擊與回合結算
        if (actionPerformed) {
            roundCount++;
            Monster* m = (Monster*)gameEntities[1];
            if (m->getHp() > 0) {
                if (m->checkCharge()) {
                    if (!dodged) m->attack(gameEntities[0], 2);
                    else std::cout << ">> 你閃開了蓄力攻擊！" << std::endl;
                    m->setCharge(false);
                } else {
                    if (rand() % 3 == 0) {
                        std::cout << ">> 怪物正在蓄力！" << std::endl;
                        m->setCharge(true);
                    } else if (!dodged) m->attack(gameEntities[0]);
                    else std::cout << ">> 怪物攻擊被你閃開了！" << std::endl;
                }
            } else {
                std::cout << "!!! 擊殺怪物！" << std::endl;
                killCount++;
                delete gameEntities[1];
                gameEntities[1] = new Monster("怪物", 0, 0, 0);
            }
            gameEntities[0]->reduceCooldown();
        }
    }
    std::cout << "\n遊戲結束！共擊殺: " << killCount << " 隻，總回合: " << roundCount << std::endl;
    for(Entity* e : gameEntities) delete e;
    return 0;
}