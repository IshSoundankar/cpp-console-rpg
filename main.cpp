#include "ItemsDB.h"
#include <iostream>
#include <vector>
#include <memory>
#include <characters.hpp>
#include <items.hpp>
#include <board.hpp>
#include <stdlib.h>
using namespace std;

void attack(Character* attacker, Character* defender){

    cout << attacker->name << "attacks " << defender->name << endl;
    float attackRoll = (float)rand() / RAND_MAX;
    if (attackRoll > attacker->attack_chance) {
        cout << attacker->name << " missed!" << endl;
        return;
    }
    float defenceRoll = (float)rand() / RAND_MAX;
    if (defenceRoll < defender->defence_chance) {
        defender->successfulDef(attacker,defender);
        return;
    }

    if (attacker->getTotalAttack()>defender->getTotalDefence()){
        int damage = attacker->getTotalAttack() - defender->getTotalDefence();
        defender->health -=damage;
        if (defender->health < 0) defender->health = 0;
        cout << defender->name << " takes "<<damage<<" hits of damage"<<endl;
        cout << defender->name <<" health: "<<defender->getTotalHealth()<<endl;
        if (defender->health > defender->getTotalHealth()) defender->health = defender->getTotalHealth();

    }
    else{
        cout<<defender->name<<" blocked the attack";
    }
    if (defender->getTotalHealth() <=0){
        cout << defender->name<<" defeated"<<endl;
    }

}
shared_ptr<Character> player;
shared_ptr<Character> enemy;

void user(shared_ptr<Character>& player){
    int choice;
    Human tempHuman("Human");
    Elf tempElf("Elf");
    Dwarf tempDwarf("Dwarf");
    Hobbit tempHobbit("Hobbit");
    Orc tempOrc("Orc");

    string user;
    cout << "Enter Name: "<<endl;
    cin >> user;
    cout << "Select race of player: " << endl;
    cout << "1." << endl;
    tempHuman.printStats();
    cout << "2." << endl;
    tempElf.printStats();
    cout << "3." << endl;
    tempDwarf.printStats();
    cout << "4." << endl;
    tempHobbit.printStats();
    cout << "5." << endl;
    tempOrc.printStats();

    while (true) {
    cout << "Enter your choice (1-5): " << endl;
    if (cin >> choice && choice >= 1 && choice <= 5) break;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid choice" << endl;
}

    switch(choice){
    case 1: player = make_shared<Human>(user);break;
    case 2: player = make_shared<Elf>(user);break;
    case 3: player = make_shared<Dwarf>(user);break;
    case 4: player = make_shared<Hobbit>(user);break;
    case 5: player = make_shared<Orc>(user);break;

    }
    system("cls");
    cout << "You selected: ";
    player->printStats();

}

void currentStats(int playerRow, int playerColumn,shared_ptr<Character> player, int gold){


    cout <<"Current location: " << playerRow << " "<< playerColumn << endl;

    player->printStats();
    cout << "Gold: " << gold<<endl;

    }



int main()
{
    int commandCount = 0;
    bool isNight = false;   // Start as day

    vector<shared_ptr<Character>> enemies;
    enemies.push_back(make_shared<Human>("Bob"));
    enemies.push_back(make_shared<Elf>("Legolas"));
    enemies.push_back(make_shared<Dwarf>("Gimli"));
    enemies.push_back(make_shared<Hobbit>("Frodo"));
    enemies.push_back(make_shared<Orc>("Azog"));

    // 2. Use ItemsDB for items
    vector<shared_ptr<Item>> items;
    items.push_back(Sword);
    items.push_back(Dagger);
    items.push_back(LeatherArmor);
    items.push_back(PlateArmor);
    items.push_back(RingOfLife);
    items.push_back(RingOfStrength);
    items.push_back(LargeShield);
    items.push_back(SmallShield);
    Board board(8,8);
    board.populateBoard(enemies, items);
    user(player);
    int playerRow = 0;
    int playerColumn = 0;
    int gold = 0;

    char choice;
    bool gameOver = false;
    while(!gameOver){
        cout << "Enter command (w/a/s/d = move, g = pickup, j = attack, h = drop, k = look, l = inventory, x = exit): "<<endl;
        cin >> choice;
        system("cls");

        board.grid[playerRow][playerColumn]->player = nullptr;


    switch (choice) {
        case 'w':
            cout << "moving up"<<endl;        // up
            if (playerRow > 0) playerRow--;
            commandCount++;
            break;
        case 's': // down
            cout << "moving down"<<endl;        // up
            if (playerRow < board.height - 1) playerRow++;
            commandCount++;
            break;
        case 'a': // left
            cout << "moving left"<<endl;        // up
            if (playerColumn > 0) playerColumn--;
            commandCount++;
            break;

        case 'd': // right
            cout << "moving right"<<endl;        // up
            if (playerColumn < board.width - 1) playerColumn++;
            commandCount++;
            break;

    case 'h':
            cout << "Drop what? (1=Weapon, 2=Armour, 3=Shield, 4=Ring): ";
            char slot;
            cin >> slot;
            if (slot == '1') {
                player->dropWeapon();
            } else if (slot == '2') {
                player->dropArmour();
            } else if (slot == '3') {
                player->dropShield();
            } else if (slot == '4') {
                // List rings
                if (player->ring.empty()) cout << "No rings to drop." << endl;
                else {
                    cout << "Which ring? ";
                    for (size_t i = 0; i < player->ring.size(); ++i)
                        cout << i+1 << ") " << player->ring[i]->name << "  ";
                    int rnum;
                    cin >> rnum;
                    player->dropRing(rnum-1); // -1 for zero-based index
                }
            } else {
                cout << "Invalid choice." << endl;
            }
            commandCount++;
            break;

    case 'j': {
        cout << "attack" << endl;
        auto& enemyOnSquare = board.grid[playerRow][playerColumn]->enemy;
        player->printStats();
        if (enemyOnSquare) {
            enemyOnSquare->printStats();
            attack(player.get(), enemyOnSquare.get());

            if (enemyOnSquare->getTotalHealth() <= 0) {
                cout << enemyOnSquare->race << " Defeated!  Received 20 gold!" << endl;
                board.grid[playerRow][playerColumn]->enemy = nullptr;
                gold += 20;
                bool anyEnemiesLeft = false;
                for (int r = 0; r < board.height; ++r) {
                    for (int c = 0; c < board.width; ++c) {
                        if (board.grid[r][c]->enemy) {
                            anyEnemiesLeft = true;
                            break;
                        }
                    }
                    if (anyEnemiesLeft) break;
                }
                if (!anyEnemiesLeft) {
                    cout << "Congratulations! You defeated all the enemies and won the game!" << endl;
                    gameOver = true;
                }
                break;
            }

            attack(enemyOnSquare.get(), player.get());
            if (player->getTotalHealth() <= 0) {
                cout << "You Died! \n Game over!" << endl;
                gameOver = true;
            }
        } else {
            cout << "No enemy to attack" << endl;
        }
        commandCount++;

        break;
    }


    case 'k':
        cout<<"Look"<<endl;
        cout<< "Information about current square: "<<endl;
        board.grid[playerRow][playerColumn]->printInfo();
        commandCount++;
        break;


    case 'l':
        player->printInventory();
        cout <<"Total gold collected: " <<gold << endl;;
        commandCount++;

        break;
    case 'g':{
        cout << "pickup";
        auto& itemOnSquare = board.grid[playerRow][playerColumn]->item;
        if(itemOnSquare) {
            if (player->pickUp(itemOnSquare)) {
                itemOnSquare = nullptr;
            }
        } else {
            cout << "No item here!" << endl;

        }
    }
        commandCount++;

        break;
    case 'x':
        cout << "Exit"<<endl;
        gameOver = true;
        break;

    default:

        cout << "Enter correct input"<<endl;

        break;
    }
    if (commandCount % 10 < 5) {
        if (isNight) {
            isNight = false;
            cout << "It is now daytime." << endl;
            // <<< Add this block here: >>>
            for (int r = 0; r < board.height; ++r) {
                for (int c = 0; c < board.width; ++c) {
                    auto enemyPtr = board.grid[r][c]->enemy;
                    if (enemyPtr) {
                        Orc* orcPtr = dynamic_cast<Orc*>(enemyPtr.get());
                        if (orcPtr) {
                            orcPtr->setTimeOfDay(isNight);
                        }
                    }
                }
            }
        }
    } else {
        if (!isNight) {
            isNight = true;
            cout << "It is now night." << endl;
            // <<< Add this block here: >>>
            for (int r = 0; r < board.height; ++r) {
                for (int c = 0; c < board.width; ++c) {
                    auto enemyPtr = board.grid[r][c]->enemy;
                    if (enemyPtr) {
                        Orc* orcPtr = dynamic_cast<Orc*>(enemyPtr.get());
                        if (orcPtr) {
                            orcPtr->setTimeOfDay(isNight);
                        }
                    }
                }
            }
        }
    }


    board.grid[playerRow][playerColumn]->player = player;
    currentStats(playerRow, playerColumn, player,gold);
    board.printBoard();


    }

    return 0;
}
