#pragma once
#include <memory>
#include <string>
#include <vector>
#include "items.hpp"
using namespace std;

class Character {
public:
    string name;
    string race;
    int attack;
    float attack_chance;
    int defence;
    float defence_chance;
    int health;
    int strength;
    shared_ptr<Weapon> weapon;
    shared_ptr<Armour> armor;
    shared_ptr<Shield> shield;
    vector<shared_ptr<Ring>> ring;
    vector<shared_ptr<Item>> inventory;

    Character(string n, string r, int a, float ac, int d, float dc, int h, int s)
    {
        name = n;
        race = r;
        attack = a;
        attack_chance = ac;
        defence = d;
        defence_chance = dc;
        health = h;
        strength = s;
    }
    virtual void printStats() = 0;
    shared_ptr<Item> item;

    bool pickUp(shared_ptr<Item>item) {
        if(getCurrentWeight() + item->weight>getTotalStrength()){

            cout<<"Item too heavy"<<endl;
            return false;
        }
        if (auto w = dynamic_pointer_cast<Weapon>(item)) {
            weapon = w;
            w->print();
            return true;
        }
        if (auto s = dynamic_pointer_cast<Shield>(item)) {
            shield = s;
            s->print();
            inventory.push_back(item);
            return true;
        }
        // Armour
        if (auto a = dynamic_pointer_cast<Armour>(item)) {
            armor = a;
            a->print();
            inventory.push_back(item);
            return true;
        }
        // Ring: can carry many
        
            if(auto r = dynamic_pointer_cast<Ring>(item)) {
            ring.push_back(r);
            r->print();
            inventory.push_back(item);
            return true;
        }
        // Add similar for other categories if needed
        cout << "Item not recognized." << endl;
        return false;

    }
    void printInventory() {
        cout << "Equipped Items:" << endl;
        if (weapon) { cout << "Weapon: "; weapon->print(); }
        else cout << "Weapon: None" << endl;

        if (armor) { cout << "Armour: "; armor->print(); }
        else cout << "Armour: None" << endl;

        if (shield) { cout << "Shield: "; shield->print(); }
        else cout << "Shield: None" << endl;

        if (ring.empty())
            cout << "Rings: None" << endl;
        else {
            cout << "Rings:" << endl;
            for (size_t i = 0; i < ring.size(); ++i) {
                cout << "  " << i+1 << ". ";
                ring[i]->print();
            }
        }
    }


   virtual void successfulDef(Character* attacker, Character* defender) ;

    int getCurrentWeight() const {
        int total = 0;
        if (weapon) total += weapon->weight;
        if (armor) total += armor->weight;
        if (shield) total += shield->weight;
        for (const auto& r : ring) total += r->weight;
        return total;
    }

    int getTotalAttack() const {
        int total = attack;
        if (weapon) total += weapon->attack_inc;
        if (armor) total -= armor->attack_dec;
        if (shield) total -= shield->attack_dec;
        for (const auto& r : ring) total += r->strength_inc;
        return total;
    }
    int getTotalDefence() const{
        int total = defence;
        if(armor) total +=armor->defence_inc;
        if(shield) total +=shield->defence_inc;
        return total;
    }
    int getTotalStrength() const {
        int total = strength;
        for (const auto& r : ring) total += r->strength_inc;
        return total;
    }

    int getTotalHealth() const {
        int total = health;
        for (const auto& r : ring) total += r->health;
        return total;
    }

    void dropWeapon() {
        if (weapon) {
            cout << "Dropping weapon: " << weapon->name << endl;
            weapon = nullptr;
        } else {
            cout << "No weapon to drop.\n";
        }
    }

    void dropArmour() {
        if (armor) {
            cout << "Dropping armor: " << armor->name << endl;
            armor = nullptr;
        } else {
            cout << "No armor to drop.\n";
        }
    }

    void dropShield() {
        if (shield) {
            cout << "Dropping shield: " << shield->name << endl;
            shield = nullptr;
        } else {
            cout << "No shield to drop.\n";
        }
    }

    void dropRing(int index) {
        if (index >= 0 && index < (int)ring.size()) {
            cout << "Dropping ring: " << ring[index]->name << endl;
            ring.erase(ring.begin() + index);
        } else {
            cout << "Invalid ring choice.\n";
        }
    }




};

class Human : public Character{
public:
    Human(string n) : Character(n,"Human", 30, 2.0/3.0, 20, 0.5 , 60, 100){}
    virtual void printStats() override{
        cout << name << ", race: " <<race << ", attack: "<< getTotalAttack() << ", defence: "<< getTotalDefence() << ", health: "<< getTotalHealth() << ", strength: "<< getTotalStrength() << endl;
    }
    void successfulDef(Character* attacker, Character* defender) override;
};

class Elf : public Character{
public:
    Elf(string n) : Character(n,"Elf", 40, 1.0, 10, 0.25, 40, 70){}
    virtual void printStats() override{
        cout << name << ", race: " <<race << ", attack: "<< getTotalAttack() << ", defence: "<< getTotalDefence() << ", health: "<< getTotalHealth() << ", strength: "<< getTotalStrength() << endl;
    }
    void successfulDef(Character* attacker, Character* defender) override;

};

class Dwarf : public Character{
public:
    Dwarf(string n) : Character(n,"Dwarf", 30, 2.0/3.0, 20, 2.0/3.0, 50, 130){}
    virtual void printStats() override{
        cout << name << ", race: " <<race << ", attack: "<< getTotalAttack() << ", defence: "<< getTotalDefence() << ", health: "<< getTotalHealth() << ", strength: "<< getTotalStrength() << endl;
    }
    void successfulDef(Character* attacker, Character* defender) override;

};

class Hobbit : public Character{
public:
    Hobbit(string n) : Character(n,"Hobbit", 25, 1.0/3.0, 20, 2.0/3.0, 70, 85){}
    virtual void printStats() override{
        cout << name << ", race: " <<race << ", attack: "<< getTotalAttack() << ", defence: "<< getTotalDefence() << ", health: "<< getTotalHealth() << ", strength: "<< getTotalStrength() << endl;
    }
    void successfulDef(Character* attacker, Character* defender) override;

};

class Orc : public Character {
public:
    bool isNight;

    Orc(string n) : Character(n, "Orc", 25, 0.25, 10, 0.25, 50, 130), isNight(false) {}

    void setTimeOfDay(bool night) {
        isNight = night;
        if(isNight) {
            attack = 45;
            attack_chance = 1.0;
            defence = 25;
            defence_chance = 0.5;
        } else {
            attack = 25;
            attack_chance = 0.25;
            defence = 10;
            defence_chance = 0.25;
        }
    }

    void printStats() override {
        cout << "Orc " << name << " stats: "
             << "Attack: " << getTotalAttack() << ", Defence: " << getTotalDefence() << ", Health: " << getTotalHealth() << ", Strength: " << getTotalStrength()
             << (isNight ? " [Night]" : " [Day]") << endl;
    }
    void successfulDef(Character* attacker, Character* defender) override;

};

