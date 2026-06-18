#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <cstdlib>

class Entity {
protected:
    std::string name;
    int hp, atk, skillCooldown;
public:
    Entity(std::string n, int h, int a, int cd = 0) : name(n), hp(h), atk(a), skillCooldown(cd) {}
    virtual ~Entity() {}
    
    virtual void useSkill(Entity* target) = 0;
    
    // 開放必要的 getter 用於存檔
    int getAtk() const { return atk; }
    int getHp() const { return hp; }
    int getCd() const { return skillCooldown; }

    void takeDamage(int damage) { hp -= damage; if (hp < 0) hp = 0; }
    void attack(Entity* target, int multiplier = 1) {
        int dmg = atk * multiplier;
        std::cout << name << " 造成了 " << dmg << " 點傷害！" << std::endl;
        target->takeDamage(dmg);
    }

    void reduceCooldown() { if (skillCooldown > 0) skillCooldown--; }
    bool canUseSkill() const { return skillCooldown == 0; }
    void setCooldown(int cd) { skillCooldown = cd; }
};

class Warrior : public Entity {
public:
    // 支援從存檔讀入 CD 值
    Warrior(std::string n, int h, int a = 20, int cd = 0) : Entity(n, h, a, cd) {}
    void useSkill(Entity* target) override {
        std::cout << ">>> 勇者發動強力重擊！" << std::endl;
        target->takeDamage(atk * 2);
        setCooldown(2);
    }
};

class Monster : public Entity {
private:
    bool isCharging;
public:
    // 支援從存檔讀入 HP, ATK, CD
    Monster(std::string n, int h = 0, int a = 0, int cd = 0) 
        : Entity(n, (h == 0 ? (rand() % 50 + 80) : h), (a == 0 ? (rand() % 5 + 8) : a), cd), isCharging(false) {}
    
    bool checkCharge() { return isCharging; }
    void setCharge(bool state) { isCharging = state; }
    void useSkill(Entity* target) override {
        std::cout << ">>> 怪物劇毒反擊！" << std::endl;
        target->takeDamage(atk * 1.5);
        setCooldown(3);
    }
};

#endif