#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "characters.hpp"
#include "items.hpp"

using namespace std;

class Character;
class Item;

class Square{
public:
    shared_ptr<Character> enemy;
    shared_ptr<Item> item;
    shared_ptr<Character> player;
    void printInfo(){

        if(enemy){

            cout<<"Enemy here: " <<endl;
            enemy->printStats();
        }
        if(item){

            cout <<"Item here: " << endl;
            item->print();
        }
        if(player){
            cout <<"Player here: "<<endl;
            player->printStats();
        }

        if(!enemy && !item && !player){
            cout<<"Square is empty!"<<endl;
        }
    }
};

class Board{
public:
    int width;
    int height;
    vector<vector<shared_ptr<Square>>> grid;

    Board(int w, int h){

        width = w;
        height = h;
        grid.resize(height);
        for (int i = 0; i < height; ++i) {

            grid[i].resize(width);
            for(int j = 0; j<width;j++){
                grid[i][j] = make_shared<Square>();
            }
        }
    }
    void printBoard(){

        for (int i = 0; i < height; ++i) {
            for(int j = 0; j<width;j++){

                cout << "|" <<(grid[i][j]->player ? "#" :(grid[i][j]->enemy ? "*" : (grid[i][j]->item ? "+" : " " ))) << "|";

            }
            cout << endl;
        }

    }
    void populateBoard(const vector<shared_ptr<Character>>, const vector<shared_ptr<Item>>);

};
