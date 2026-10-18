#include "board.hpp"
#include <cstdlib> // rand, srand
#include <ctime>

void Board::populateBoard(const vector<shared_ptr<Character>> enemies, const vector<shared_ptr<Item>> item){

    srand(time(nullptr));

    for(int i = 0;i < enemies.size();i++){
        shared_ptr<Character> enemyPointer = enemies[i];
        int x = rand() % height;
        int y = rand() % width;


        while(grid[x][y] -> enemy !=nullptr){

                x=rand() % height;
                y=rand() % width;
            }

    grid[x][y]->enemy=enemyPointer;
}
    for(int i = 0;i < item.size();i++){
        shared_ptr<Item> itemPointer = item[i];
        int x = rand() % height;
        int y = rand() % width;


        while(grid[x][y] ->enemy !=nullptr || grid[x][y]->item !=nullptr){

                x=rand() % height;
                y=rand() % width;
            }

    grid[x][y]->item=itemPointer;
    }

}
