#include "characters.hpp"
#include <iostream>
#include <cstdlib> // for rand()

void Character::successfulDef(Character* attacker, Character* defender){
}

void Human::successfulDef(Character* attacker, Character* defender){
    cout << defender->name<<" defended successfully!"<<endl;

}
void Elf::successfulDef(Character* attacker, Character* defender){
    cout << defender->name<<" defended successfully!"<<endl;
    defender ->health +=1;
    cout << defender->name<<" health increased to "<<defender->health<<endl;
}
void Dwarf::successfulDef(Character* attacker, Character* defender){
    cout << defender->name<<" defended successfully!"<<endl;

}
void Hobbit::successfulDef(Character* attacker, Character* defender){
    cout << defender->name<<" defended successfully!"<<endl;
    defender->health -=rand() % 6;
    if (defender->health < 0) defender->health = 0;
    cout << defender->name<<" health reduced to "<<defender->health<<endl;

}
void Orc::successfulDef(Character* attacker, Character* defender){
    if(!isNight){
        int temp = attacker->getTotalAttack() - defender->getTotalDefence();
        if (temp < 0) temp = 0;
        int damageTaken = temp / 4;  // quarter damage
        defender->health -= damageTaken;
        if (defender->health < 0) defender->health = 0;
        cout << defender->name << " partially blocked, took " << damageTaken << " damage" << endl;
    }
    else{
        defender ->health +=1;
        cout << defender->name<<" health increased to "<<defender->health<<endl;

    }
}
