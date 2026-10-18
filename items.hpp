#pragma once
#include <string>
#include <iostream>
using namespace std;

class Item {
public:
    string name;
    int weight;

    Item(string n, int w) {
        name = n;
        weight = w;
    }
    virtual void print(){
        cout << name << "(Weight: "<< weight << endl;
    }
    virtual ~Item(){}
};

class Weapon : public Item{
public:
    int attack_inc;

    Weapon(string n,int w, int atk) : Item(n,w)

    {
        attack_inc = atk;
    }
    virtual void print() override {
        cout << name << "(Weapon, Attack + "<<attack_inc << ",Weight: " << weight <<endl;
    }
};

class  Armour : public Item{
public:

    int defence_inc;
    int attack_dec;

    Armour(string n, int w, int def, int atk) : Item(n,w)
    {
        defence_inc = def;
        attack_dec = atk;

    }
    virtual void print() override {
        cout << name << "(Armour, Defence + "<<defence_inc << ", Attack - " << attack_dec << ",Weight: " << weight <<endl;
    }

};


class  Shield : public Armour{
public:
    Shield(string n, int w, int def, int atk) : Armour(n,w,def,atk){}
        virtual void print() override {
        cout << name << "(Shield, Defence + "<<defence_inc << ", Attack - " << attack_dec << ",Weight: " << weight <<endl;
    }
};

class Ring : public Item {
public:
    int health;        // can be positive or negative
    int strength_inc;  // can be positive or zero

    Ring(string n, int w, int hel, int str)
        : Item(n, w), health(hel), strength_inc(str) {}

    void print() override {
        cout << name << " (Ring, Health "
             << (health >= 0 ? "+" : "") << health
             << ", Strength + " << strength_inc
             << ", Weight: " << weight << ")\n";
    }
};
